import grequests
import requests
import secrets as s
from time import perf_counter

# secrets.py
# username = "xxxx"
# repo = "xxxx"
# token = "xxxx"

startTime = perf_counter()

def timer():
    return "{:>10.4f}".format(perf_counter() - startTime)

userInput = str(input("Only delete successful runs?(Y/n):")).lower()

# get workflow runs
url = "https://api.github.com/repos/" + s.username + "/" + s.repo + "/actions/runs?per_page=100"
if "y" in userInput:
    url += "&status=success"
idList = []
r = requests.get(url).json()
count = r["total_count"]
print(timer(), "Count:", count)
urlList = []
for i in range(1, count // 100 + 2):
    urlList.append(url + "&page=" + str(i))
resultList = grequests.map((grequests.get(u) for u in urlList))
for i in resultList:
    r = i.json()
    r = r["workflow_runs"]
    for runs in r:
        idList.append(runs["id"])
print(timer(), "Actural Count:", len(idList))
idList.reverse()  # delete old runs first

# delete
print(timer(), "Deleting...")
header = {"Authorization": "token " + s.token}
url = "https://api.github.com/repos/" + s.username + "/" + s.repo + "/actions/runs/"
urlList = []
for idx, runId in enumerate(idList):
    urlList.append(url + str(runId))
    if (idx + 1) % 10 == 0:
        grequests.map((grequests.delete(u, headers=header) for u in urlList))
        print(timer(), str(idx + 1) + " runs was deleted.")
        urlList = []

print(timer(), "Finished")

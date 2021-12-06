import requests
import secrets as s

# get workflow runs
url = "https://api.github.com/repos/" + s.username + "/" + s.repo + "/actions/runs?per_page=100&status=success"
idList = []
r = requests.get(url).json()
count = r["total_count"]
print("Count:", count)
for i in range(1, count // 100 + 2):
    r = requests.get(url + "&page=" + str(i)).json()
    r = r["workflow_runs"]
    for runs in r:
        idList.append(runs["id"])
print("Actural Count:", len(idList))

# delete
print("Deleting...")
header = {"Authorization": "token " + s.token}
url = "https://api.github.com/repos/" + s.username + "/" + s.repo + "/actions/runs/"
for runId in idList:
    requests.delete(url + str(runId), headers=header)

print("Finished")

import asyncio
import sys
from pyrogram import Client
from pyrogram.raw import functions
from secrets import *
from re import fullmatch, IGNORECASE

app = None


async def async_readline(prompt: str = "") -> str:
    await async_print(prompt, end="")
    return await asyncio.get_event_loop().run_in_executor(
        None, lambda: sys.stdin.readline().strip())


async def async_print(*values: object, sep: str = ' ', end: str = '\n'):
    await asyncio.get_event_loop().run_in_executor(
        None,
        lambda v=values, s=sep, e=end: print(*v, sep=s, end=e, flush=True))


async def login():
    global app
    app = Client("my_account", api_id, api_hash, proxy=proxy)
    await app.start()
    print("Ok")


async def testMsg():
    async_print("Send test msg")
    await app.send_message("me", "Greetings from **Pyrogram**!")


async def get_all_chats():
    await async_print("Get all chats")
    res = await app.invoke(functions.messages.GetAllChats(except_ids=[]))
    await async_print(len(res))


async def send_msg():
    await async_print("Send text")
    chat_id = await async_readline("id:")
    msg = await async_readline("msg:")
    await app.send_message(chat_id, msg)

async def sending_progress(current, total):
    await async_print(f"{current * 100 / total:.1f}%", current, total)

async def send_pic():
    await async_print("Send photo")
    chat_id = await async_readline("id:")
    pic = await async_readline("photo:")
    await app.send_photo(chat_id, pic, progress=sending_progress)


async def send_vid():
    await async_print("Send video")
    chat_id = await async_readline("id:")
    vid = await async_readline("video:")
    await app.send_video(chat_id, vid, progress=sending_progress)


async def main():
    while True:
        await async_print("Type command:")
        cmd = await async_readline()

        if fullmatch("quit|q|exit|e", cmd, IGNORECASE):
            exit(0)

        if fullmatch("login|l", cmd, IGNORECASE):
            await login()
        elif app is None:
            await async_print("Plz login first.")
            continue

        if fullmatch("test", cmd, IGNORECASE):
            await testMsg()
        elif fullmatch("all", cmd, IGNORECASE):
            await get_all_chats()
        elif fullmatch("msg", cmd, IGNORECASE):
            await send_msg()
        elif fullmatch("pic", cmd, IGNORECASE):
            await send_pic()
        elif fullmatch("vid", cmd, IGNORECASE):
            await send_vid()


asyncio.run(main())

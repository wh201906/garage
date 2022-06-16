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
    await async_print("Ok")


async def testMsg():
    await async_print("Send test msg")
    await app.send_message("me", "Greetings from **Pyrogram**!")


async def get_all_chats():
    await async_print("Get all chats")
    cnt = 0
    async for dialog in app.get_dialogs():
        chat = dialog.chat
        await async_print(
            "type:", chat.type, "id:", chat.id, "title:", chat.first_name
            or chat.title, "restricted:", "Y"
            if hasattr(chat, "is_restricted") and chat.is_restricted else "N")
        cnt += 1
    await async_print("count:", cnt)


async def send_msg():
    await async_print("Send text")
    chat_id = await async_readline("chat id:")
    msg = await async_readline("msg:")
    await app.send_message(chat_id, msg)


async def sending_progress(current, total):
    await async_print(f"{current * 100 / total:.1f}%", current, total)


async def send_pic():
    await async_print("Send photo")
    chat_id = await async_readline("chat id:")
    pic = await async_readline("photo:")
    await app.send_photo(chat_id, pic, progress=sending_progress)


async def send_vid():
    await async_print("Send video")
    chat_id = await async_readline("chat id:")
    vid = await async_readline("video:")
    await app.send_video(chat_id, vid, progress=sending_progress)


async def get_msgs():
    await async_print("Get messages")
    chat_id = await async_readline("chat id:")
    num = await app.get_chat_history_count(chat_id)
    await async_print("num:", num)
    # peer = await app.resolve_peer(chat_id)
    # res = await app.invoke(
    #     functions.messages.GetHistory(peer=peer,
    #                                   offset_id=0,
    #                                   add_offset=0,
    #                                   limit=50,
    #                                   max_id=999999999,
    #                                   min_id=0,
    #                                   hash=0,
    #                                   offset_date=0))
    # await async_print(res)
    offset = await async_readline("offset:")
    async for msg in app.get_chat_history(chat_id, 100):
        await async_print("type:", msg.media, "id:", msg.id, "text:", msg.text)


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
        elif fullmatch("gmsgs", cmd, IGNORECASE):
            await get_msgs()


asyncio.run(main())

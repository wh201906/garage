import asyncio
import sys
from pyrogram import Client
from pyrogram.raw import functions
from pyrogram.enums import MessageMediaType
from pyrogram.errors import FloodWait
from tgutils import *
from re import match, fullmatch, IGNORECASE

app = None


async def sync():
    global app
    print("Sync")

    source_id = await get_chat_id("source chat id:")
    target_id = await get_chat_id("target chat id:")

    hide_source = get_bool_input("Hide message source?")
    skip_existing = get_bool_input("skip existing messages?", True)
    offset = int(input("offset(default is 0):"))

    type_filter = input("type list[All,Text,Photo,Video]:")
    sync_text = match("all|text", type_filter, IGNORECASE) is not None
    sync_photo = match("all|photo", type_filter, IGNORECASE) is not None
    sync_video = match("all|video", type_filter, IGNORECASE) is not None

    existing = set()
    if skip_existing:
        async for msg in app.get_chat_history(target_id):
            if msg.media is None:
                continue
            elif msg.media == MessageMediaType.PHOTO and sync_photo:
                existing.add(msg.photo.file_unique_id)
            elif msg.media == MessageMediaType.VIDEO and sync_video:
                existing.add(msg.video.file_unique_id)
            elif msg.media == MessageMediaType.VIDEO_NOTE and sync_video:
                existing.add(msg.video_note.file_unique_id)

    num = await app.get_chat_history_count(source_id)
    cnt = offset
    async for msg in app.get_chat_history(source_id, offset=offset):
        cnt += 1

        if msg.media is None and not sync_text:
            continue
        elif msg.media == MessageMediaType.PHOTO and (
                not sync_photo or
            (skip_existing and msg.photo.file_unique_id in existing)):
            continue
        elif msg.media == MessageMediaType.VIDEO and (
                not sync_video or
            (skip_existing and msg.video.file_unique_id in existing)):
            continue
        elif msg.media == MessageMediaType.VIDEO_NOTE and (
                not sync_video or
            (skip_existing and msg.video_note.file_unique_id in existing)):
            continue

        try:
            if hide_source:
                await app.copy_message(target_id, source_id, msg.id)
            else:
                await app.forward_messages(target_id, source_id, msg.id)
        except FloodWait as e:
            await asyncio.sleep(e.value)

        print("\r{}/{} {:.4f}%".format(cnt, num, cnt / num * 100), end="")
        sys.stdout.flush()
    print("")


async def main():
    global app
    while True:
        print("Type command:")
        cmd = input()

        if fullmatch("quit|q|exit|e", cmd, IGNORECASE):
            exit(0)

        if fullmatch("login|l", cmd, IGNORECASE):
            app = await login()
        elif not is_logged_in():
            print("Plz login first.")
            continue

        elif fullmatch("all", cmd, IGNORECASE):
            await get_all_chats()
        elif fullmatch("msg", cmd, IGNORECASE):
            await send_text()
        elif fullmatch("chats", cmd, IGNORECASE):
            await get_all_chats()
        elif fullmatch("sync", cmd, IGNORECASE):
            await sync()


asyncio.run(main())

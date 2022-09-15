import asyncio
import sys
from pyrogram import Client
from secrets import *
from re import fullmatch, IGNORECASE

# ************* secrets.py begin *************
# api_id=<8-digit number>
# api_hash='<32 hex symbols>'
# proxy = {
#     "scheme": "socks5",
#     "hostname": "localhost",
#     "port": xxxx,
# }
# *************  secrets.py end  *************

app = None


async def login():
    global app, api_id, api_hash
    if 'proxy' in globals().keys():
        print("Using proxy")
        app = Client("my_account", api_id, api_hash, proxy=proxy)
    else:
        app = Client("my_account", api_id, api_hash)

    await app.start()
    print("Logged in")
    return app


async def logout():
    global app
    await app.log_out()
    app = None


def is_logged_in():
    global app
    return app is not None


async def send_text():
    global app
    print("Send text")
    chat_id = input("chat id:")
    msg = input("msg:")
    await app.send_message(chat_id, msg)
    print("text was sent")


async def get_all_chats():
    global app
    print("Get all chats")
    cnt = 0
    async for dialog in app.get_dialogs():
        chat = dialog.chat
        print(
            "type:", chat.type, "id:", chat.id, "title:", chat.first_name
            or chat.title, "restricted:", "Y"
            if hasattr(chat, "is_restricted") and chat.is_restricted else "N")
        cnt += 1
    print("count:", cnt)


def get_bool_input(msg: str, default: bool = False):
    result = input(msg + "[Yes|No|True|False]")
    if fullmatch("yes|y|true|t", result, IGNORECASE):
        return True
    elif fullmatch("no|n|false|f", result, IGNORECASE):
        return False
    else:
        return default


async def get_chat_id(msg: str):
    global app
    result = input(msg)
    if fullmatch("me|self", result, IGNORECASE):
        return "me"
    elif result[0] == "-":  # chat id(int)
        return int(result)
    elif result[0] == "+":  # phone number(str)
        return result
    else: # get available ids
        id_list = [dialog.chat.id async for dialog in app.get_dialogs()]
        for id in id_list:
            if id == int(result): # interpret as id(int)
                return id
        return result # interpret as phone number(str)
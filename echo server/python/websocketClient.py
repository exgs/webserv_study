#!/usr/bin/env python

import asyncio
import websockets

async def hello():
    async with websockets.connect("ws://localhost:8765") as websocket:
        await websocket.send("Hello world!")
        strTemp = await websocket.recv()
        print(strTemp)

asyncio.run(hello())
print("Done")
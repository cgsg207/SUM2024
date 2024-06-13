import http from "node:http";
import fs from "node:fs/promises";
import path from "node:path";
import process from "node:process";
import express from "express";
import { WebSocketServer } from "ws";

let count = 0;

const app = express();
app.get("/", (req, res, next) => {
    count = count + 1;
    console.log(count);
    next();
});
app.get("/getSecretData", (req, res, next) => {
    res.send(`Secret Data received: ${count}`);
});
app.use(express.static("client"));

const server = http.createServer(app);

const wss = new WebSocketServer({ server });

wss.on("connection", (ws) => {
    ws.on("message", (message) => {
        console.log(message.toString());
        ws.send(`Message: ${message}`);
    });
    ws.send("Client connected");
});
const host = "localhost";
const port = 8080;

server.listen(port, host, () => {
    console.log(`Server started on http://${host}:${port}`);
});

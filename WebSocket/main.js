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

wss.on("connectoin", (ws) => {
    ws.on("message", (massage) => {
        console.log(message);
        ws.send(`Message: ${message}`);
    });
    ws.send("Client connected");
});
const host = "localhost";
const port = 8080;

server.listen(port, host, () => {
    console.log(`Server started on http://${host}:${port}`);
});

// const requestListener = (req, res) => {
//   res.setHeader("Content-Type", "text/html");
//   res.writeHead(200);
//   res.end(`<html><body><h1>HTML response</h1><body></html>`);
// };

// const requestListener = async (req, res) => {
//   const contents = await fs.readFile(process.cwd() + "/index.html");
//   res.setHeader("Content-Type", "text/html");
//   res.writeHead(200);
//   res.end(contents);
// };

// const requestListener = async (req, res) => {
//     if (req.url == "/") {
//         const contents = await fs.readFile(
//             process.cwd() + "/client/index.html",
//         );
//         res.setHeader("Content-Type", "text/html");
//         res.writeHead(200);
//         res.end(contents);
//     } else {
//         if (req.url.endsWith(".js")) {
//             const contents = await fs.readFile(
//                 process.cwd() + "/client" + req.url,
//             );
//             res.setHeader("Content-Type", "text/javascript");
//             res.writeHead(200);
//             res.end(contents);
//         }
//     }
// };

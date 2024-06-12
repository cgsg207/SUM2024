import { f } from "./b.js";

console.log("ABC");
f();

setInterval(async () => {
    const response = await fetch("/getSecretData");
    const text = await response.text();

    console.log(text);
    const elem = document.getElementById("SecretDataField");
    elem.textContent = text;
}, 1000);

function Communication() {
    let socket = WebSocket("ws://localhost:8080");

    socket.onopen = (event) => {
        console.log("Socket open");
        socket.send("From client");
    };

    socket.onmessage = (event) => {
        console.log(`Message received: ${event.data}`);
    };
}

Communication();

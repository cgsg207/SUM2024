/*setInterval(async () => {
    const response = await fetch("/getSecretData");
    const text = await response.text();

    console.log(text);
    const elem = document.getElementById("SecretDataField");
    elem.textContent = text;
}, 1000); */

/*function Communication() {
    let socket = new WebSocket("ws://localhost:8080");

    socket.onopen = (event) => {
        console.log("Socket open");
        socket.send("From client");
    };

    socket.onmessage = (event) => {
        console.log(`Message received: ${event.data}`);
    };
}

Communication();*/

let socket = new WebSocket("ws://localhost:8080");

socket.onopen = (event) => {
    console.log("Socket open");
    socket.send("Add client");
};

export function SendMessage() {
    const message_text = document.getElementById("message");
    const name_text = document.getElementById("name");

    if (typeof message_text == "undefined" || typeof name_text == "undefined") {
        socket.send("Error");
    }

    console.log("Button");
}

function initComunication() {
    socket.onmessage = (event) => {
        console.log(`Message received: ${event.data}`);
    };
}

initComunication();

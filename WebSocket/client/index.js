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
    //socket.send("Add client");
};

export function SendMessage() {
    const message_text = document.getElementById("message");
    const name_text = document.getElementById("name");
    const text = document.getElementById("info");

    if (
        typeof message_text == "undefined" ||
        typeof name_text == "undefined" ||
        message_text == null ||
        name_text == null
    ) {
        socket.send("Error");
    }

    if (name_text.value == "") {
        text.value += "Error: empty name";
    }
    if (message_text.value == "") {
        text.value += "Error: empty message";
    }

    console.log("Button");
}

function initComunication() {
    socket.onmessage = (text) => {
        const info = document.getElementById("info");
        info.value += text.data;
    };
}

export function initClear() {
    const info = document.getElementById("info");
    info.value = "";
}

initComunication();

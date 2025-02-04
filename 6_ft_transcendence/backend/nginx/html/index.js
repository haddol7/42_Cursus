console.log("hello!")

let socket = null;

function setSocket(value) {    
    socket = io("/game", {
        path: "/game-sio/",
        auth: {
            user_id: value,
            user_name: "name"
        }
    });
    
    console.log(socket)
    
    socket.on("connect", () => {
        console.log(`connect with user_id=${value}`);
    });
    
    socket.on("connect_error", (error) => {
        console.log("connect error, ", error);
    });
    
    socket.on("disconnect", (reason, details) => {
        console.log("disconnect: ", reason, details);
    });

    socket.on("init", (data) => {
        console.log("init", data);
    });
    socket.on("updateScore", (data) => {
        console.log("updateScore", data);
    });
    socket.on("updatePaddle", (data) => {
        console.log("updatePaddle", data);
    });
    socket.on("updateBall", (data) => {
        console.log("updateBall", data);
    });
    socket.on("gameOver", (data) => {
        console.log("gameOver", data);
    });
    socket.on("resetPositions", (data) => {
        console.log("resetPositions", data);
    });
}

function onSubmit() {
    const inputText = document.querySelector("input#user_id");
    console.dir(inputText);
    const value = inputText.valueAsNumber;
    setSocket(value);

    return false;
}

function emitNextGame() {
    socket.emit("nextGame");
}
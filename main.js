document.forms['count-rows'].addEventListener('submit', (event) => {
    event.preventDefault();
    console.log("Submission For: ",event.target.value);
    fetch(event.target.action, {
        method: 'POST',
        body: new URLSearchParams(new FormData(event.target))
    }).then((response) => {
        if (!response.ok) {
            throw new Error(response.statusText);
        }
        return response.json();
    }).then((body) => {
        console.log(body);
    }).catch((error) => {
        console.error(error);
    });
    render();
});

document.getElementById('#button').addEventListener('click', (event) => {
    event.preventDefault();
    console.log("Button Clicked");
    var el = document.getElementById('button-indicator');
    if (el.innherHTML == "Not Pressed") {
        el.innerHTML = "Pressed";
    } else {
        el.innerHTML = "Not Pressed";
    }
    render();
});
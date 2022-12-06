var open_file = function(e) {
    const file_reader = new FileReader();
    file_reader.onload = (event) => {
      const uint8Arr = new Uint8Array(event.target.result);
      const num_bytes = uint8Arr.length * uint8Arr.BYTES_PER_ELEMENT;
      const data_ptr = Module._malloc(num_bytes);
      const data_on_heap = new Uint8Array(Module.HEAPU8.buffer, data_ptr, num_bytes);
      data_on_heap.set(uint8Arr);
      const res = Module.ccall('load_file', 'number', ['number', 'number'], [data_on_heap.byteOffset, uint8Arr.length]);
      Module._free(data_ptr);
    };
    file_reader.readAsArrayBuffer(e.target.files[0]);
};

const inputElement = document.getElementById("file-upload-count-rows");
inputElement.addEventListener("change", handleFiles, false);
function handleFiles() {
  console.log("time to handle files");
  const fileList = this.files; /* now you can work with the file list */
  console.log(fileList);
}

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
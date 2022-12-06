// Get the input and button elements
const csvFileInput = document.getElementById('csv-file');
const uploadButton = document.getElementById('upload-button');
const downloadButton = document.getElementById('download-button');

// Handle the click event for the upload button
uploadButton.addEventListener('click', () => {
  // Check if a file has been selected
  if (!csvFileInput.files.length) {
    alert('Please select a CSV file to upload.');
    return;
  }

  // Read the CSV file
  const reader = new FileReader();
  reader.onload = async () => {

    console.log('Loading WebAssembly module...');
    let wasmModule;
    let importObject;
    if (!importObject) {
      importObject = {
        imports: {
          processCsv: (processCsv, csvResult) => {
            return processCsv(csvResult);
          }
        }
      };
    }
    if(!WebAssembly.instantiateStreaming) {
      console.log("WebAssembly.instantiateStreaming not supported");
      const response = await fetch('email_processor.wasm');
      const bytes = await response.arrayBuffer();
      const module = await WebAssembly.compile(bytes);
      wasmModule = await WebAssembly.instantiate(module, importObject);
    } else {
      console.log("WebAssembly.instantiateStreaming supported");
      const response = await fetch('email_processor.wasm');
      wasmModule = await WebAssembly.instantiateStreaming(response, importObject);
    }
    console.log('WebAssembly module loaded.');

    // Call the WebAssembly function to process the CSV data
    const processCsv = instance.exports.processCsv;
    const csvString = processCsv(reader.result);

    // Enable the download button
    downloadButton.disabled = false;

    // Handle the click event for the download button
    downloadButton.addEventListener('click', () => {
      // Create a URL for the CSV data
      const csvUrl = URL.createObjectURL(new Blob([csvString]));

      // Create a link to the CSV file
      const link = document.createElement('a');
      link.setAttribute('href', csvUrl);
      link.setAttribute('download', 'deduped_emails.csv');

      // Add the link to the page
      document.body.appendChild(link);

      // Click the link to download the CSV file
      link.click();
    });   
  };
  reader.readAsText(csvFileInput.files[0]);
});

const { contextBridge, ipcRenderer } = require("electron");

contextBridge.exposeInMainWorld("ipcAPIs", {
  on_driver_data: (callback) =>
    ipcRenderer.on("driver_data", (e, data) => {
      callback(data);
    }),
  next_question: ()=> {ipcRenderer.send('asynchronous-message', 'ping')}
});
  
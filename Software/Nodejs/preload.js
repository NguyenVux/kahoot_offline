const {ipcRenderer,contextBridge} = require("electron")


contextBridge.exposeInMainWorld("main_api",{
    driver_data_callback: (callback) =>{ipcRenderer.on("driver_data",(evt,data)=>callback(data));}
}
)
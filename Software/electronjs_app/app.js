const { create } = require('domain')
const { app, BrowserWindow, ipcMain} = require('electron')
const path = require('path')
const driver = require("./driver")

function create_window()
{
  return new BrowserWindow({
    webPreferences: {
      contextIsolation: false,
      nodeIntegration: true,
      preload: path.join(__dirname,"preload.js")
    }
  })
}


app.once("ready",()=>
{
  const window = create_window();
  window.loadFile("index.html")
  window.webContents.on("devtools-opened", (event) => { 
    event.preventDefault();
    window.webContents.closeDevTools(); 
  });
})

app.allowRendererProcessReuse = false
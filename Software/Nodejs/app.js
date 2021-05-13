const {Driver} = require("./driver")
const {load_setting} = require("./common")
const { app, BrowserWindow } = require('electron')
const path = require('path')
const config = load_setting(path.join(__dirname,"config.json"))


config["webPreferences"]["preload"] = path.join(__dirname,"preload.js")



app.whenReady().then(() => {
  let win = new BrowserWindow(config)
  win.loadFile("index.html")
  let driver = new Driver({config_file_name:"driver_config.json"})
  driver.connect("COM5")
  driver.on_data = (data) => {
      win.webContents.send("driver_data",data)
  }
})

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit()
  }
})
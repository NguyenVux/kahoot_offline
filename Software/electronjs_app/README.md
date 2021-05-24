# Document for 

### **To install all package in package.json run this command:**
#### Node version - v14.16.1
```
    $ npm install
```

### **driver.js**
```javascript
    const driver = require("./driver.js") // Import driver

    driver.on("data",callback(data)) // add handler when there is incoming data
```
### **driver_config.json**
```json
    {
        "port":"COM5", // port name: 
        "baudRate": 115200, //baudrate speed
        "delimiter": [170,10] //Array of delimiter
    }
```

### **Edit main UI script in UI.js**

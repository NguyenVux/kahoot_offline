const SerialPort = require("serialport");
const Delimiter = require("@serialport/parser-delimiter");
const { Transformer } = require("stream");
const Event = require("events");
const { join: join_path } = require("path");
const { load_setting } = require("../common");

const bufferable = new Set(["string", "buffer"]);
const buffer_size = 7;

class Driver extends Event {
  constructor({ config_file_name } = {}) {
    super()
    if (typeof config_file_name !== "string")
      throw new Error("config_file_name is not a string");
    this.config = load_setting(join_path(__dirname, config_file_name));
    this.config["autoOpen"] = false;
    console.log(this.config);
    this.parser = new Delimiter(this.config);
    this.is_writing = false;
    this.parser.on("data", (data) => {
      this.emit("data", this.#data_parser(data));
    });
  }
  get available_port() {
    return SerialPort.list();
  }
  async connect(path) {
    return new Promise((resolve, reject) => {
      this.port = new SerialPort(path, this.config);
      this.port.pipe(this.parser);
      this.port.on("open", () => {
        this.port.removeAllListeners("error");
        this.port.on("error",e=>this.emit("error",e))
        resolve(true);
      });
      this.port.on("error",(e) => {
        reject(e);
      });

      this.port.open();
    });
  }
  write(data) {
    if (this.port.isOpen && !this.is_writing)
    {
        this.is_writing = true;
        this.port.write(data)
        this.port.on("finish",()=>this.is_writing=false)
    }
  }
  #data_parser(data) {
    if (!Buffer.isBuffer(data)) {
      this.emit(
        "error",
        new Error(`Expected buffer type\nbut recieved ${typeof data}`)
      );
      return;
    }
    if (data.length != buffer_size) {
      this.emit(
        "error",
        new RangeError(
          `\nExpected buffer size: ${buffer_size}B\nrecieve: ${data.length}B`
        )
      );
      return;
    }
    return {
      mac: Array.from(data.slice(0, 5)).join(":"),
      value: Math.log2(data[6]),
    };
  }
}

module.exports = {
  Driver: Driver,
};


<!-- 7/1/2020
## <b>Todo:</b>
### esp32 hiện có 3 cách giao tiếp
1. WIFI host/ client thông qua router  (lượng data lớn, tốn điện nên bỏ) 
2. BLE (bluetooth low energy) (lượng data nhỏ, ít tốn điện)
3. ESP_NOW (một dạng protocal mới phát triển dựa trên wifi của espressif) tốn điện nhưng range (khoảng cách giao tiếp) cao hơn nhiều so với wifi hay BLE (lượng data nhỏ, tương đối ít tốn điện)
### Hiện mình đang có 2 vấn đề cần các bạn nghiên cứu để chọn sau khi có board để test nha :D hoặc nếu chưa có mn seach gg thêm thông tin vào file này cũng được nha thks
1. ESP_NOW có sẵn API nhưng số lượng kết nối trong khoảng từ 6-20 thiết bị (có thể sẽ thiếu) mình chưa tìm hiểu sâu nhưng cũng có thể tăng số lượng thì phải, ESP_NOW thì tương thích với ESP8266 (lap dư số lượng để test đó)
2. BLE cũng có sẵn NHIỀU APIs (tạm gọi nha) như:
- BLE connect Peer-to-Peer (kết nối và truyền tín hiệu liên tục giữa 2 nút, Qa coi sơ qua thì thấy kết nối được khoảng 6 cái) https://www.esp32.com/viewtopic.php?t=954
- BLE MESH
https://www.youtube.com/watch?v=GG8JtFNiHw0 thấy cũng được đó :v nhưng không thấy nhận mà chỉ gửi nhanh thôi 
- BLE BOARDCAST (chưa rõ nhiều cái boardcast sẽ sảy ra chuyện gì)
<br/> Dựa trên 2 chuẩn protocal là GAP và GATT. doc: https://www.espressif.com/sites/default/files/documentation/esp32_bluetooth_architecture_en.pdf  -->

### 9/1/2020
Thí nghiệm #1 số lượng esp8266 có thể gửi cùng lúc mà không gây ra lỗi gì
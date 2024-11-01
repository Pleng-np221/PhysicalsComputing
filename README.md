# Physical Computing Project 2024 - IT KMITL
โครงการนี้เป็นส่วนหนึ่งในรายวิชา PHYSICAL COMPUTING ภาคเรียนที่ 1 ปีการศึกษา 2567 ของคณะเทคโนโลยีสารสนเทศ สาขาเทคโนโลยีสารสนเทศ สถาบันเทคโนโลยีพระจอมเกล้าเจ้าคุณทหารลาดกระบัง

# **บทคัดย่อ รายละเอียดโครงงาน**
โครงงานนี้เป็นการใช้ไมโครคอนโทรลเลอร์ในการพัฒนาระบบตรวจจับแก๊สและเปลวไฟ โดยมีวัตถุประสงค์เพื่อสร้างระบบที่สามารถตรวจสอบสภาพแวดล้อมและแจ้งเตือนผู้ใช้เมื่อมีแก๊สหรือลุกไหม้เกิดขึ้น ระบบประกอบด้วยเซนเซอร์ตรวจจับแก๊ส MQ-2, เซนเซอร์ตรวจจับเปลวไฟ, และเซนเซอร์วัดอุณหภูมิ รวมถึง Buzzer สำหรับเสียงเตือน และ LCD สำหรับการแสดงผล

ระบบทำงานโดยการรับข้อมูลจากเซนเซอร์ต่าง ๆ เพื่อตรวจสอบระดับแก๊สและการเกิดเปลวไฟ หากมีการตรวจพบอันตราย ระบบจะส่งเสียงเตือนผ่าน Buzzer พร้อมกับแสดงสถานะบน LED Matrix นอกจากนี้ยังมีการส่งข้อความแจ้งเตือนผ่าน Telegram เพื่อให้ผู้ใช้ได้รับข้อมูลในทันที

โครงงานนี้ไม่เพียงแต่ช่วยเพิ่มความปลอดภัยในสภาพแวดล้อมที่มีความเสี่ยงต่อการเกิดอุบัติเหตุจากแก๊สหรือเปลวไฟ แต่ยังเป็นการฝึกทักษะด้านการเขียนโปรแกรมและการทำงานร่วมกับฮาร์ดแวร์ของไมโครคอนโทรลเลอร์อีกด้วย

# [**[WEBSITE LINK]**](https://pleng-np221.github.io/PhysicalsComputing/)

# **PROJECT POSTER**
<img src="https://github.com/Pleng-np221/PhysicalsComputing/blob/main/images/projectPosterPNG.png?raw=true" width="1080">

# **PROJECT DEMO VIDEO**


# **อุปกรณ์ที่ใช้**
| **ลำดับ** | **ชื่ออุปกรณ์** | **รูปภาพ** |
|-----------|------------------|-------------|
| 1 | Arduino® UNO R4 WiFi| <img src="https://github.com/user-attachments/assets/18c37a8a-e643-49c5-b1ca-4a1c482f3752" width="150"> |
| 2 | Buzzer | <img src="https://github.com/user-attachments/assets/5f26151b-f50c-4a10-a3a3-21097e944af2" width="150"> |
| 3 | โมดูลตรวจจับแก๊สและควัน MQ-2 | <img src="https://github.com/user-attachments/assets/523f801a-303c-47c0-8edd-86b386b5b160" width="150"> |
| 4 | จอแสดงผล LCD 1602 with I2C| <img src="https://makerzone.com.au/wp-content/uploads/2021/12/1602-lcd-green-2.jpg" width="150"> |
| 5 | เซนเซอร์วัดอุณหภูมิ temperature sensor mcp9700| <img src="https://static.cytron.io/image/cache/catalog/products/SN-MCP-9700/SN-MCP-9700-800x800.jpg" width="150"> |
| 6 | เซนเซอร์ตรวจจับเปลวไฟ Flame Sensor | <img src="https://github.com/user-attachments/assets/17c710fd-9b8f-4df8-9fdd-39218fa45f41" width="150"> |
| 7 | Solenoid Valve 5VDC | <img src="https://down-th.img.susercontent.com/file/1f6519d59e3463fcb6b7494d4784cb1d@resize_w450_nl.webp" width="150"> |
| 8 | Relay Module 5V | <img src="https://fa.lnwfile.com/_/fa/_raw/7f/2a/c3.jpg" width="150"> |
| 9 | Power Supply - Battery| <img src="https://eclats-antivols.fr/28767-large_default/2-battery-ultrafire-37v-4200mah-18650-rechargeable-liion-3a-flashlight-tled3wz.jpg" width="150"> |
| 10 | Battery Case| <img src="https://diyables.io/images/products/4-aa-battery-holder-battery-storage-case-with-wire-lead-4-x-1.5v-6v.jpg" width="150"> |

# **ขั้นตอนการทำ**
1. **เตรียมอุปกรณ์**: Arduino, MQ-2 gas sensor, flame sensor, temperature sensor, Buzzer, solenoid valve, LED Matrix, Wi-Fi module, และสายไฟ

2. **การต่อวงจร**:
   - เชื่อมต่อเซนเซอร์และ Buzzer กับ Arduino ตามขาที่กำหนด
   - เชื่อมต่อปั๊มน้ำ， Relay Module และ Power Supply
   - เชื่อมต่อ LCD และ Wi-Fi module

3. **เขียนโค้ด**: ใช้โค้ดสำหรับตรวจสอบสถานะเซนเซอร์ ควบคุมปั๊มน้ำ และส่งข้อความผ่าน Telegram

4. **ทดสอบระบบ**: ตรวจสอบการเชื่อมต่อ อัพโหลดโค้ด และทดสอบการทำงานในสภาพแวดล้อมที่แตกต่างกัน

5. **ตรวจสอบผลลัพธ์**: ดูการแสดงผลบน LCD และเสียงจาก Buzzer รวมถึงข้อความที่ส่งผ่าน Telegram

6. **การปรับปรุง**: ปรับค่าและตรวจสอบค่าต่าง ๆ เพื่อเพิ่มประสิทธิภาพของระบบ

# **INPUT OUTPUT**
- **Input**: ข้อมูล Wi-Fi (ชื่อ Wi-Fi และรหัสผ่าน), ข้อมูล Telegram (token ของบอทและ chat ID), ค่าสัญญาณจากเซนเซอร์ตรวจจับแก๊ส (MQ-2), อุณหภูมิจากเซนเซอร์วัดอุณหภูมิ, และค่าสัญญาณจากเซนเซอร์ตรวจจับเปลวไฟ เพื่อนำไปตรวจสอบสถานะสภาพแวดล้อม เช่น การมีเปลวไฟ อุณหภูมิสูง หรือแก๊สรั่ว

- **Output**:  การแสดงภาพบน LCD, เสียงแจ้งเตือนผ่าน Buzzer, การทำงานของปั๊มน้ำ, และการส่งข้อความแจ้งเตือนผ่าน Telegram เพื่อแจ้งเตือนสถานะของระบบตามข้อมูลที่ตรวจพบ

# สมาชิกผู้จัดทำ
|ชื่อ | นามสกุล	| รหัสนักศึกษา|
|---|---|---|
|นางสาวกัญญากร | กลิ่นเอี่ยม | 66070011|
|นางสาวณัฐธิดา | พิมพา | 66070059|
|นายพีรณัฐ | เจริญพานทอง | 66070137|
|นางสาวกลิ่น | เกิดอยู่ | 66070237|

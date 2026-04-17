# 🚀 OLED ESP8266 Showcase

> Eksperimen tampilan OLED menggunakan ESP8266 ✨
> Dari teks sederhana hingga animasi ekspresi robot 🤖

![ESP8266 OLED](https://img.shields.io/badge/ESP8266-OLED-blue?style=for-the-badge)
![Arduino](https://img.shields.io/badge/Arduino-Compatible-green?style=for-the-badge)

---

## 📖 Deskripsi Project

Project ini berisi kumpulan contoh penggunaan **OLED display (SSD1306)** dengan **ESP8266**.
Cocok untuk pemula hingga menengah yang ingin belajar menampilkan teks, animasi, dan visual interaktif sederhana.

Terdapat **3 demo utama**:

* 📝 Basic Text Display
* 🔁 Running Text (Scrolling)
* 🤖 Robot Expression Animation

---

## 🧰 Hardware yang Dibutuhkan

* ESP8266 (NodeMCU / Wemos D1 Mini)
* OLED Display SSD1306 (I2C, 128x64)
* Kabel jumper
* Breadboard (opsional)

---

## 🔌 Wiring

| OLED | ESP8266 |
| ---- | ------- |
| VCC  | 3.3V    |
| GND  | GND     |
| SCL  | D1      |
| SDA  | D2      |

---

## 📦 Library

Install library berikut melalui Arduino Library Manager:

* U8g2lib

Alternatif

* Adafruit GFX
* Adafruit SSD1306

---

## 📂 Struktur Project

```
oled-esp8266/
│
├── basic_text.ino
│
├── running_text.ino
│
├── robot.ino
│
└── README.md
```

---

## 📝 1. Basic Text

Menampilkan teks statis pada layar OLED.

**Fitur:**

* Teks sederhana
* Ringan dan cepat
* Cocok untuk belajar dasar OLED

---

## 🔁 2. Running Text

Menampilkan teks berjalan dari kanan ke kiri.

**Fitur:**

* Animasi scrolling
* Bisa untuk notifikasi atau display info
* Mudah dimodifikasi

---

## 🤖 3. Robot Expression

Menampilkan animasi ekspresi wajah robot.

**Fitur:**

* Mata berkedip 👀
* Ekspresi berubah (senang, netral, mengantuk)
* Cocok untuk proyek interaktif

---

## ▶️ Cara Menjalankan

1. Buka Arduino IDE
2. Pilih board: **ESP8266**
3. Upload salah satu file `.ino`
4. Pastikan wiring sudah sesuai
5. OLED akan langsung menampilkan output

---

## 💡 Ide Pengembangan

* Tambahkan sensor (PIR, ultrasonic)
* Integrasi dengan WiFi (IoT)
* Tambahkan tombol untuk kontrol
* Buat menu interface di OLED

```

---

## 🤝 Kontribusi

Kontribusi terbuka untuk siapa saja.
Silakan fork, modifikasi, dan buat pull request 🚀

---

## 📜 Lisensi

Menggunakan lisensi **MIT** — bebas digunakan, dimodifikasi, dan didistribusikan.

---

## ⭐ Dukungan

Jika project ini membantu, jangan lupa kasih ⭐ di repository GitHub!

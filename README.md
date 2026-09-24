# aPPgame_console_esp8266MODEMCU

Game console based on ESP8266 NodeMCU and an OLED display.
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 1000 600" width="100%" height="100%">
  <style>
    .bg { fill: #1a1a1a; }
    .title { fill: #ffffff; font-family: system-ui, -apple-system, sans-serif; font-size: 26px; font-weight: bold; text-anchor: middle; }
    .box { fill: #24292e; stroke: #008080; stroke-width: 3; rx: 12; }
    .mcu { fill: #2d333b; stroke: #414b56; stroke-width: 3; rx: 12; }
    .mcu-chip { fill: #c8d1d9; rx: 6; }
    .btn-box { fill: #2d333b; stroke: #6e7681; stroke-width: 2; rx: 8; }
    
    .text-chip { fill: #1c2128; font-family: sans-serif; font-size: 20px; font-weight: bold; text-anchor: middle; }
    .text-chip-sub { fill: #57606a; font-family: sans-serif; font-size: 16px; text-anchor: middle; }
    .text-oled { fill: #00ffff; font-family: sans-serif; font-size: 18px; font-weight: bold; text-anchor: middle; }
    
    .pin-label { fill: #8b949e; font-family: sans-serif; font-size: 15px; font-weight: bold; }
    .pin-mcu { fill: #c9d1d9; font-family: sans-serif; font-size: 16px; font-weight: 500; }
    
    .btn-text { fill: #ffffff; font-family: sans-serif; font-size: 15px; font-weight: bold; }
    .note { fill: #8b949e; font-family: sans-serif; font-size: 15px; text-anchor: middle; }
    
    .wire { fill: none; stroke-width: 3; }
    .wire-gnd-dash { fill: none; stroke: #8b949e; stroke-width: 2; stroke-dasharray: 6,6; }
  </style>

  <!-- Background -->
  <rect class="bg" width="100%" height="100%" />

  <!-- Main Title -->
  <text x="500" y="45" class="title">Connection Diagram: ESP8266 + OLED SSD1306 + 4 Buttons</text>

  <!-- OLED Display -->
  <rect x="60" y="215" width="200" height="170" class="box" stroke="#00d2d2" />
  <rect x="75" y="260" width="170" height="100" fill="#000000" />
  <text x="160" y="318" class="text-oled">OLED 128x64</text>
  
  <!-- OLED Pins -->
  <circle cx="98" id="p-vcc" cy="215" r="5" fill="#e53935" />
  <circle cx="138" id="p-gnd" cy="215" r="5" fill="#757575" />
  <circle cx="178" id="p-scl" cy="215" r="5" fill="#fbc02d" />
  <circle cx="218" id="p-sda" cy="215" r="5" fill="#03a9f4" />
  
  <text x="98" y="200" class="pin-label" text-anchor="middle">VCC</text>
  <text x="138" y="200" class="pin-label" text-anchor="middle">GND</text>
  <text x="178" y="200" class="pin-label" text-anchor="middle">SCL</text>
  <text x="218" y="200" class="pin-label" text-anchor="middle">SDA</text>

  <!-- ESP8266 NodeMCU -->
  <rect x="372" y="95" width="256" height="420" class="mcu" />
  <rect x="428" y="110" width="144" height="120" class="mcu-chip" />
  <text x="500" y="165" class="text-chip">ESP8266</text>
  <text x="500" y="195" class="text-chip-sub">NodeMCU</text>

  <!-- NodeMCU Left Pins -->
  <text x="388" y="260" class="pin-mcu">3V3</text>
  <text x="388" y="310" class="pin-mcu">GND</text>
  <text x="388" y="360" class="pin-mcu">D1 (SCL)</text>
  <text x="388" y="410" class="pin-mcu">D2 (SDA)</text>
  
  <circle cx="372" cy="255" r="5" fill="#e53935" />
  <circle cx="372" cy="305" r="5" fill="#757575" />
  <circle cx="372" cy="355" r="5" fill="#fbc02d" />
  <circle cx="372" cy="405" r="5" fill="#03a9f4" />

  <!-- NodeMCU Right Pins -->
  <text x="612" y="260" class="pin-mcu" text-anchor="end">D5 (UP)</text>
  <text x="612" y="310" class="pin-mcu" text-anchor="end">D6 (DOWN)</text>
  <text x="612" y="360" class="pin-mcu" text-anchor="end">D7 (LEFT)</text>
  <text x="612" y="410" class="pin-mcu" text-anchor="end">D4 (RIGHT)</text>
  
  <circle cx="628" cy="255" r="5" fill="#4caf50" />
  <circle cx="628" cy="305" r="5" fill="#ff9800" />
  <circle cx="628" cy="355" r="5" fill="#ab47bc" />
  <circle cx="628" cy="405" r="5" fill="#ec407a" />

  <!-- OLED Wires -->
  <path d="M 98 215 L 98 165 L 350 165 L 350 255 L 372 255" class="wire" stroke="#e53935" />
  <path d="M 138 215 L 138 180 L 335 180 L 335 305 L 372 305" class="wire" stroke="#757575" />
  <path d="M 178 215 L 178 195 L 320 195 L 320 355 L 372 355" class="wire" stroke="#fbc02d" />
  <path d="M 218 215 L 218 405 L 372 405" class="wire" stroke="#03a9f4" />

  <!-- Buttons Group -->
  <!-- BTN UP -->
  <rect x="748" y="140" width="64" height="64" class="btn-box" />
  <circle cx="780" cy="172" r="22" fill="#4caf50" />
  <text x="825" y="177" class="btn-text">- BTN UP (D5)</text>
  <path d="M 628 255 L 712 255 L 712 172 L 748 172" class="wire" stroke="#4caf50" />

  <!-- BTN DOWN -->
  <rect x="748" y="225" width="64" height="64" class="btn-box" />
  <circle cx="780" cy="257" r="22" fill="#ff9800" />
  <text x="825" y="262" class="btn-text">- BTN DOWN (D6)</text>
  <path d="M 628 305 L 748 305" class="wire" stroke="#ff9800" />

  <!-- BTN LEFT -->
  <rect x="748" y="310" width="64" height="64" class="btn-box" />
  <circle cx="780" cy="342" r="22" fill="#ab47bc" />
  <text x="825" y="347" class="btn-text">- BTN LEFT (D7)</text>
  <path d="M 628 355 L 712 355 L 712 342 L 748 342" class="wire" stroke="#ab47bc" />

  <!-- BTN RIGHT -->
  <rect x="748" y="395" width="64" height="64" class="btn-box" />
  <circle cx="780" cy="427" r="22" fill="#ec407a" />
  <text x="825" y="432" class="btn-text">- BTN RIGHT (D4)</text>
  <path d="M 628 405 L 700 405 L 700 427 L 748 427" class="wire" stroke="#ec407a" />

  <!-- GND Shared Line -->
  <path d="M 320 305 L 320 515 L 912 515 L 912 172" class="wire-gnd-dash" />

  <!-- Bottom Note -->
  <text x="500" y="535" class="note">--- The second contacts of all buttons are connected together and wired to GND ---</text>
</svg>


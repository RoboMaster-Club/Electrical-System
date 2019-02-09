# Power Distribution Board
The power distibution board is used to deliver 24V power for the entire robot by @cmkz97

## Feature
1. `Voltage Divier for ADC to monitoring voltage in real time`
   1. with variable resistor for adjustment
2. `Temperature Monitoring IC using I2C`
   1. Enabled by <a href = 'http://ww1.microchip.com/downloads/en/DeviceDoc/25095A.pdf'>MCP9808M</a>
3. `Hall Effect Currentl Monitor Up to 15A`
   1. IC Used  <a href = 'https://www.allegromicro.com/~/media/Files/Datasheets/ACS723-Datasheet.ashx?la=en&hash=1800BF05ABE975CB295D729784D3AEABF820A0DC'>ACS723</a>
   2. <b>Pls becareful of the MAX current rating. This same chip has multiple serial number that has different MAX current Seting</b>


## Todos
1. [ ] I faild to consider that the Flywheel draws up to 30A OF CURRENT.... I NEED MORE RESEARCH

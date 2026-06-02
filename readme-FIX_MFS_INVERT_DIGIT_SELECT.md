# readme-fix-MFS_INVERT_DIGIT_SELECT-problem

## Add compatibility option for active-low digit select displays

This note documents a compatibility issue found in some Arduino Multi Function Shield clones that use two `74HC595` shift registers to drive the 4-digit display.

The tested board uses the same display pins as the classic Multi Function Shield:

```text
DATA  = D8
CLOCK = D7
LATCH = D4
```

However, the 4-digit display did not work correctly with the original library behavior. The display powered on, but showed malformed characters instead of values such as `1234`.

After direct tests with the `74HC595` output, the display worked correctly when digit selection was treated as active LOW.

## Diagnosis

The tested display configuration is:

```text
DATA  = D8
CLOCK = D7
LATCH = D4
Segments = standard segment mapping
Digit select = active LOW
```

The working digit select values are:

```cpp
digit 0 = 0xFE
digit 1 = 0xFD
digit 2 = 0xFB
digit 3 = 0xF7
```

## Proposed compatibility option

This patch adds a compile-time compatibility flag:

```cpp
#ifndef MFS_INVERT_DIGIT_SELECT
#define MFS_INVERT_DIGIT_SELECT 1
#endif
```

Use:

```cpp
#define MFS_INVERT_DIGIT_SELECT 1
```

for displays that require active-LOW/inverted digit select.

Use:

```cpp
#define MFS_INVERT_DIGIT_SELECT 0
```

for the original/classic library behavior.

## Implementation

The patch keeps the existing segment maps and adds two helper functions:

```cpp
static inline byte normalizeSegmentValue(byte value)
{
#if MFS_INVERT_DIGIT_SELECT
  return ~value;
#else
  return value;
#endif
}

static inline byte normalizeDigitSelect(byte segment)
{
#if MFS_INVERT_DIGIT_SELECT
  return (byte)(0xF0 | ((~(1 << segment)) & 0x0F));
#else
  return SEGMENT_SELECT[segment];
#endif
}
```

The low-level display writing routine then sends:

```cpp
byte valueOut = normalizeSegmentValue(Value);
byte digitOut = normalizeDigitSelect(Segment);
```

This keeps the hardware adaptation isolated and documented.

## Test sketch

```cpp
#include <MultiFuncShield.h>

void setup() {
  MFS.initialize();
}

void loop() {
  MFS.write(1234);
  delay(1500);

  MFS.write(5678);
  delay(1500);

  MFS.write(8888);
  delay(1500);

  MFS.write(1111);
  delay(1500);

  MFS.write("Hi");
  delay(1500);

  MFS.write("End");
  delay(1500);
}
```

Expected output:

```text
1234
5678
8888
1111
Hi
End
```

## Pull Request title suggestion

```text
Add compatibility option for active-low digit select displays
```

## Notes

- No hardware modification was required.
- The issue was not caused by changed DATA/CLOCK/LATCH pins.
- The same D8/D7/D4 pin configuration was confirmed by direct tests.
- The compatibility option preserves the classic behavior when disabled.

# Keyball Core Function Library

## Scroll snap mode

When scrolling with the trackball, the scroll direction is restricted.
This restriction is called "scroll snap".

The direction of restriction can be changed using special key codes.
You can also release this restriction.
It is called as "scroll snap mode"
The current mode is displayed on the OLED.

There are 3 modes for scroll snap.

1. Vertical (default): key code is `SSNP_VRT`, indicated as `VT`.
2. Horizontal: key code is `SSNP_HOR`, indicated as `HO`.
3. Free: key code is `SSNP_FRE`, indicated as `SCR`.

The scroll snap mode at startup is vertical,
but you can change it by saving the current mode with `KBC_SAVE`

## MEMO

This section contains notes regarding the specifications of this library.
Since the purpose is to keep a record in whatever form it takes,
a lot of Japanese is included.
If you would like to read it in English, please request a translation via issue or discussion.
Of course you can translate it for us. If you translate it,
please make pull requests to share it with us.

### Scroll Snap Spec

This feature can be disabled by adding `#define KEYBALL_SCROLLSNAP_ENABLE 0` to `config.h`.

Scroll snap restricts the direction of scrolling with the trackball.
Currently, there are three modes for scroll snap:

* Snap to vertical direction (default)
* Snap to horizontal direction
* Free scrolling without snapping

These modes can be manually switched using the custom key codes `SSNP_VRT`, `SSNP_HOR`, and `SSNP_FRE`.

#### up to 1.3.2

By default, scrolling with the trackball is restricted (snapped) to the vertical direction.
This behavior can be enabled by adding `#define KEYBALL_SCROLLSNAP_ENABLE 1` to `config.h`.

This feature consists of snap mode and free mode.
The initial state is snap mode, where the scroll direction is restricted to vertical.
In snap mode, if you scroll horizontally in a certain direction for a certain count (default is 12), it transitions to free mode.
This count is after applying the scroll divider.
In free mode, the restriction is removed, allowing free scrolling in both horizontal and vertical directions.
If no scrolling operation is performed for a certain time (default is 100 milliseconds) in free mode, it transitions back to snap mode.

To change the count required to transition to free mode, use `KEYBALL_SCROLLSNAP_TENSION_THRESHOLD`.
To change the interval (in milliseconds) required to transition back to snap mode, use `KEYBALL_SCROLLSNAP_RESET_TIMER`.
Both can be configured in `config.h`.

Example of changing the count to 5 and the interval to 200 milliseconds:

```c
#define KEYBALL_SCROLLSNAP_TENSION_THRESHOLD 5
#define KEYBALL_SCROLLSNAP_RESET_TIMER 200
```

#### History of Scroll Snap

Initially, scrolling was completely free.
However, the ball's sensitivity was higher than expected, making it difficult to move in a single direction, which caused unintended operations.
For this reason, it was determined that some sort of snap function was necessary.

The first snap function was designed to snap to either the vertical or horizontal axis as long as the movement stayed within a certain angle.
However, during the initial phase of rotation, the movement amount was minimal, and the sensor's sensitivity was high.
This caused a problem where even when trying to move vertically, a minimal amount of horizontal movement was detected, making the snap direction unstable.
Humans were not as precise in their finger movements as they thought.

To address this, scrolling was completely disabled until a certain direction and count were detected.
This was equivalent to discarding the initial scroll amount during the start of rotation.

However, as can be easily understood by imagining a web browser, vertical scrolling is frequently used in general use cases.
The aforementioned discarding caused a delay in vertical scrolling, significantly degrading the user experience.
To resolve this, a mode was introduced: initially restricted to vertical scrolling, later transitioning to free scrolling.

### Scroll Divider

The Keyball sensor is highly sensitive.
Using raw values as scroll amounts made scrolling operations very difficult.
To address this, a method was adopted where raw values are divided by a certain number before being applied to scrolling.
This divisor is called the scroll divider.

The scroll divider was limited to powers of 2, such as 1, 2, 4, 8, 16, 32, and 64, as smaller values had no practical control benefits.
If the divisor is a power of 2, it can be expressed as $2^n$, where $n$ is the exponent.
To save bits for EEPROM storage, $n$ is limited to the range of 1 to 7.
The actual divisor can be calculated using the formula:

$$ 2 ^ {(n - 1)} $$

The initial value of $n$ is 4, meaning a divisor of 1/8.
This value can be changed by defining the macro `KEYBALL_SCROLL_DIV_DEFAULT` in `config.h`.
Setting this to 0 is not considered, so avoid doing so.

### Scroll Inhibitor

Keyball manages whether the trackball's movement is applied to the pointer or scrolling using an internal mode called scroll mode.
Scroll mode can be toggled at any time via key codes or API calls.
In the default keymap, the state of a specific layer is applied to toggle scroll mode.

Initially, unintended operations frequently occurred immediately after switching scroll mode.
For example, after moving the pointer to a browser and then switching to scroll mode, unintended scrolling would occur.

To address this, all trackball operations are discarded for a certain period immediately after switching scroll mode.
This discard period is called the Scroll Inhibitor.
The default value for the Scroll Inhibitor is 50 milliseconds.
Although short, it is quite effective.

The Scroll Inhibitor can be modified by defining the macro `KEYBALL_SCROLLBALL_INHIVITOR` in `config.h`.
To disable it, set the value to `0`.
It might be interesting to try disabling it if you're curious.


# AS modules for VCV Rack

AS is a collection of modules for [VCV Rack](https://vcvrack.com/) by Alfredo Santamaria, Need a custom work?, you can find me at [Hakken.com.mx](http://www.hakken.com.mx/).

AS Logo/Monogram Copyright (c) 2017 Alfredo Santamaria , All rights reserved.
Panel graphics in res/ are © 2017
Derivative works may not use the AS logo or panel graphics including custom component graphics (knobs, switches, screws, caps,etc.).

### Releases

AS is compatible with VCV Rack 0.5.X. releases for Mac, Win and Linux are found on the [Release Page](https://github.com/AScustomWorks/as/releases)

If you enjoy those modules you can support the development by making a donation, it will be appreciated!. Here's the link: [DONATE](https://www.paypal.me/frederius/)


![AS](https://github.com/AScustomWorks/AS/blob/master/AS.JPG)

# AS modules

### ADSR
Fundamental ADSR module. Mods: graphics, sliders instead of knobs to provide faster visual input.

### VCA
Fundamental VCA module. Mods: graphics, sliders instead of knobs to provide faster visual input, one input + lin/exp switch instead of two separate inputs.

V 0.5.3: Code fix, now the VCA module works ok when there's no envelope input present.

### QuadVCA/Mixer
AS VCA module x 4, plus mixer functionality (user request).

V 0.5.5: First relase of this module.

### BPM Clock
Strum's Mental VCV Master Clock. Mods: graphics, reset trigger input and output.

V 0.5.2: all the trigger signals are 10v now, it seems that some other modules don't work fine with the correct voltages.

V 0.5.4: Fixed a reset signal issue.

V 0.5.5: 16th clock output now sends unipolar signal, just as the other outputs.

### 8 Channel Mixer
Fundamental/Autodafe mixer module. Mods: graphics, sliders for channel volume, stereo or mono output(L channel outputs L+R signal if R channel is not active). Now with main mix mute button. Beware,the default setting for each channel volume is at 70% in stead of 0%.

V 0.5.2: added MIX L & R input to chain mixers without giving up 2 mixer channels.

### Multi 2x5
2x5 Signal multiplier.

### Mono VU Meter
V 0.5.4, New module added, Mono VU Meter made to match the 8CH Mixer.

### Stereo VU Meter
V 0.5.3, New module added, Stereo VU Meter made to match the 8CH Mixer.

### 16-step Sequencer
Fundamental/Autodafe SEQ module. Mods: graphics, digital display to show the number of steps selected.

V 0.5.2: added digital display to show current sequence step so you can run/stop the sequence and tune in the current step.

V 0.5.3: added edit mode: manual trigger with current step selector buttons and blinking led light to highlight the current step. Send a row output to a NYSTHI Hot Tuna and enjoy precise step tuning!

V 0.5.4: Exposed the trigger mode settings into the panel (contextual menu is still there but it won't change the mode)

### TinySawish
RODENTMODULES MuO. Mods: graphics, smaller panel size.

V 0.5.4 Added dc blocker code, modified a bit the internal parameters.

V 0.5.5 Extendend the freq range 1 octave below.

### TinySine
VCV tutorial module. Mods: graphics, proper sine wave.

### TriLFO
Fundamental LFO module. Mods:graphics, controls stripped to the basics but you get 3 LFOS on the same space.

### Triggers
A couple of manual trigger buttons, one ON/OFF, one temporary, both with 4 trigger outputs, trigger volts knob going from 1 to 10 v output.

### Steps
Strum's Mental VCV Counters module. Mods: graphics, 3 counters, up to 64 steps each, added reset lights to the buttons.

V 0.5.4: First relase of this module.

V 0.5.5: code tweaks.

### Launch Gate
Delay the start of a flow of signals by a set number of clock ticks (TAOS request).

V 0.5.5: First relase of this module.

### Kill Gate
Cut the flow of signals after a set number of clock ticks (TAOS request).

V 0.5.6: First relase of this module.

### Signal Delay
Delay the incomming CV signal by set milliseconds, with signal thru and delayed output. You can chain several Signal Delay modules together for unlimited length of delays. (TAOS request).

V 0.5.5: First relase of this module.

### Delay Plus
Fundamental Delay module. Mods: graphics, digital display to show delay time in MS , wet signal send & return, bypass switch.

V 0.5.4: Updated look.

V 0.5.5 CHanged the time knob reading from exponential to linear, now you can set any value precisely at the whole 1 to 10k ms range.

### Phaser
Autodafe's Phaser Fx module. Mods: graphics, bypass switch.

V 0.5.4: Added CV inputs for each parameter, updated look.

### SuperDrive
Overdrive/clipping Fx module with DRIVE, TONE and GAIN parameters, to get those acid bass lines we all love!.

V 0.5.4: First relase of this module.

### Reverb
Reverb Fx module based on ML_modules reverb and Freeverb code, with DECAY, DAMP and BLEND parameters, a little bit tamed Reverb with mixed output signal.

0.5.4: First relase of this module.

### Tremolo
Tremolo Fx module with SHAPE, SPEED and BLEND parameters, and a phase switch (set your effect, duplicate the module and invert the phase for stereo tremolo setup)your Tremolo to go!.

0.5.6: First relase of this module.

### WaveShaper
HetrickCV Wave Shaper module. Mods: graphics, bypass switch.

V 0.5.2: added back the voltage range switch.

V 0.5.4: Updated look.

### Blank Panel
Blank panels in 4,6 & 8 screw spacing widths.

### Have fun!

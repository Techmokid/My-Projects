import numpy as np
from scipy.io.wavfile import write
import sounddevice as sd

# Example phone number
phone_number = "0488523566"

# DTMF frequencies
dtmf_freqs = {
    '1': (697, 1209),
    '2': (697, 1336),
    '3': (697, 1477),
    '4': (770, 1209),
    '5': (770, 1336),
    '6': (770, 1477),
    '7': (852, 1209),
    '8': (852, 1336),
    '9': (852, 1477),
    '0': (941, 1336)
}

# Parameters
sample_rate = 44100
tone_duration = 0.08
silence_duration = 3.0
volume_factor = 0.01    # For some reason this doesn't seem to be working

def generate_tone(freq1, freq2, duration, sample_rate):
    t = np.linspace(0, duration, int(sample_rate * duration), endpoint=False)
    tone = (np.sin(2 * np.pi * freq1 * t) + np.sin(2 * np.pi * freq2 * t)) * volume_factor
    return tone

def generate_dtmf_sequence(phone_number, sample_rate, tone_duration, silence_duration, volume_factor):
    sequence = np.array([], dtype=np.float32)
    
    for digit in phone_number:
        if digit in dtmf_freqs:
            freq1, freq2 = dtmf_freqs[digit]
            tone = generate_tone(freq1, freq2, tone_duration, sample_rate)
            sequence = np.concatenate((sequence, tone*0.1))
    
    # Add 3 seconds of silence at the end
    silence = np.zeros(int(sample_rate * silence_duration), dtype=np.float32)
    sequence = np.concatenate((sequence, silence))
    
    return sequence

# Generate the DTMF sequence
dtmf_sequence = generate_dtmf_sequence(phone_number, sample_rate, tone_duration, silence_duration, volume_factor)
dtmf_sequence *= volume_factor

# Normalize to 16-bit PCM range and save to WAV
dtmf_sequence = np.int16(dtmf_sequence / np.max(np.abs(dtmf_sequence)) * 32767)
write("dtmf_tones_quieter.wav", sample_rate, dtmf_sequence)

# Play the generated DTMF tones
sd.play(dtmf_sequence, sample_rate)
sd.wait()

print(f"Quieter DTMF tones for {phone_number} have been generated and saved as 'dtmf_tones_quieter.wav'.")

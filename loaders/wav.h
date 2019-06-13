// Juha Pellinen - 2015/01/06

#ifndef _WAV_H_
#define _WAV_H_

typedef struct wav_t wav_t;

#ifdef __cplusplus
extern "C" {
#endif

wav_t *wav_createFromBuffer(const void *buf);
void wav_release(wav_t *w);

unsigned int wav_getSampleRate(wav_t *w);
unsigned int wav_getBitsPerSample(wav_t *w);
unsigned int wav_getNumChannels(wav_t *w);
    
void *wav_getSampleData(wav_t *w);
unsigned int wav_getSampleDataSize(wav_t *w);
    
#ifdef __cplusplus
}
#endif

#endif

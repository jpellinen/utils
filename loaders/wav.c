#include "wav.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct wav_t
{
    unsigned int sampleRate;
    unsigned int numChannels;
    unsigned int bitsPerSample;
    
    void *sampleData;
    unsigned int sampleDataSize;
};

wav_t *wav_createFromBuffer(const void *buf)
{
    static const int PCM_COMPRESSION = 0x0001;
    
    struct wav_header {
        char riffChunkId[4];
        int32_t riffChunkSize;
        
        char waveChunkId[4];
        
        char fmtChunkId[4];
        int32_t fmtChunkSize;
        int16_t compressionCode;
        int16_t numChannels;
        int32_t sampleRate;
        int32_t avgBytesPerSec;
        int16_t blockAlign;
        int16_t bitsPerSample;
        
        char dataChunkId[4];
        int32_t dataChunkSize;
        
        void *sampleData;
    };

    const struct wav_header *h = buf;
    
    if (memcmp("RIFF", h->riffChunkId, 4) != 0 ||
        memcmp("WAVE", h->waveChunkId, 4) != 0 ||
        memcmp("fmt ", h->fmtChunkId, 4) != 0 ||
        h->compressionCode != PCM_COMPRESSION ||
        memcmp("data", h->dataChunkId, 4) != 0)
    {
        return NULL;
    }
    
    wav_t *w = malloc(sizeof(wav_t));
    w->sampleRate = h->sampleRate;
    w->numChannels = h->numChannels;
    w->bitsPerSample = h->bitsPerSample;
    w->sampleData = malloc(h->dataChunkSize);
    memcpy(w->sampleData, &h->sampleData, h->dataChunkSize);
    w->sampleDataSize = h->dataChunkSize;

    return w;
}

void wav_release(wav_t *w)
{
    free(w->sampleData);
    free(w);
}

unsigned int wav_getSampleRate(wav_t *w)
{
    return w->sampleRate;
}

unsigned int wav_getBitsPerSample(wav_t *w)
{
    return w->bitsPerSample;
}

unsigned int wav_getNumChannels(wav_t *w)
{
    return w->numChannels;
}

void *wav_getSampleData(wav_t *w)
{
    return w->sampleData;
}

unsigned int wav_getSampleDataSize(wav_t *w)
{
    return w->sampleDataSize;
}

#ifndef CODEC_H
#define CODEC_H
#include "google/protobuf/message.h"
class Codec{
public:
    google::protobuf::Message* parseFromArray();
};
#endif   // CODEC_H
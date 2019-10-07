#ifndef MSG_H
#define MSG

#include <utility>

typedef enum {MATCH ,TURN, COORDINATES, WAS_HIT, HIT_YES, HIT_NO, FINISHED } Msg_types;

struct Msg
{
    int m_sockNumFrom;
    int m_sockNumTo;
    Msg_types m_msg_type;
    std::pair<size_t, size_t> m_coordinates;
};



#endif

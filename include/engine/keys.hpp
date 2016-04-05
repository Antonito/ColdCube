#ifndef KEYS_HPP_
# define KEYS_HPP_

enum e_eventKey
  {
    KEY_Z,
    KEY_S,
    KEY_Q,
    KEY_D,
    KEY_A,
    KEY_W,
    KEY_SPACE,
#ifdef	CHEAT
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
#endif
    NB_KEY_EVENT
  };

typedef enum		e_keyboard
  {
    AZERTY_MODE,
    QWERTY_MODE
  }			e_ekeyboard;

#endif // !KEYS_HPP_


#include <stdint.h>
typedef uint16_t key_t;
#define KEY_UP (0x0800)
#define KEY_DOWN (0x0400)
#define KEY_LEFT (0x0200)
#define KEY_RIGHT (0x0100)
#define KEY_MENU (0x1000)
#define KEY_ADVANCE (0x0080)

#ifdef PLATFORM_DEFINE_VARIABLES
#define _PLATFORM_VAR
#else
#define _PLATFORM_VAR extern
#endif

_PLATFORM_VAR volatile uint16_t Platform_FrameCounter;
void Platform_init(void);
void Platform_completeFrame(void);

_PLATFORM_VAR int16_t OamMan_SpriteX;
_PLATFORM_VAR int16_t OamMan_SpriteY;
_PLATFORM_VAR uint16_t OamMan_TileId;
_PLATFORM_VAR uint8_t OamMan_Flags;
void OamMan_reset(void);
void OamMan_addSprite(void);
void OamMan_completeFrame(void);

_PLATFORM_VAR volatile key_t Keys_Held;
_PLATFORM_VAR volatile key_t Keys_Pressed;
void Keys_process(void);

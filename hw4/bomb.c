enum BombSignals {
	UP_SIG,
	DOWN_SIG,
	ARM_SIG,
	TICK_SIG
};
enum BombStates {
	SETTING_STATE,
	TIMING_STATE
};
typedef struct EventTag {
	uint16_t sig;
} Event;
typedef struct TickEvtTag {
	Event super; 
	uint8_t fine_time; 
} TickEvt;
typedef struct Bomb1Tag {
	uint8_t state;
	uint8_t timeout;
	uint8_t code; 
	uint8_t defuse;
} Bomb1;
void Bomb1_constructor
	(Bomb1 *me, uint8_t defuse);
void Bomb1_init
	(Bomb1 *me);
void Bomb1_dispatch
	(Bomb1 *me, Event const *e);
#define TRAN(target_)(me­>state = (uint8_t)(target_))
#define INIT_TIMEOUT   10

void Bomb1_dispatch(Bomb1 *me, Event const *e) {
	switch (me­>state) {
	case SETTING_STATE: {
	switch (e­>sig) {
	case UP_SIG: {
	if (me­>timeout < 60)
	display(++me­>timeout);
	break;
	}
	case DOWN_SIG: {
	if (me­>timeout > 1)
	display(­­me­>timeout);
	break;
	}
	case ARM_SIG: {
	me­>code = 0;
	TRAN(TIMING_STATE);           
	break;
	}
	}
	break;
	} /* end case SETTING_STATE */
	case TIMING_STATE: {
	switch (e­>sig) {
	case UP_SIG: {
	me­>code <<= 1; me­>code |= 1;
	break;
	}
	case DOWN_SIG: {
	me­>code <<= 1; break;
	}
	case ARM_SIG: {
	if (me­>code == me­>defuse)
	TRAN(SETTING_STATE);
	break;
	}
	case TICK_SIG: {
	if (e­>fine_time == 0) {
	display(­­me­>timeout);
	if (me­>timeout == 0)
	boom();
	}
	break;
	}
	}
	break;
	} /* end case TIMING_STATE */

void Bomb1_constructor(Bomb1 *me, uint8_t defuse) {
	me­>defuse = defuse; }
	void Bomb1_init(Bomb1 *me) {
	me­>timeout = INIT_TIMEOUT;
	TRAN(SETTING_STATE); }
	static Bomb1 l_bomb;
	int main() {
	Bomb1_constructor(&l_bomb, 0x0D);
	for (;;) { 
	static TickEvt tick_evt = { TICK_SIG, 0};
	usleep(100000);
	if (++tick_evt.fine_time == 10) {
	tick_evt.fine_time = 0;
	}
	Bomb1_dispatch(&l_bomb, (Event*)&tick_evt);
	if (kbhit())
	Bomb1_dispatch(&l_bomb, e);
	}
}
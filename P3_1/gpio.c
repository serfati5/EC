#include "44b.h"
#include "gpio.h"
#include "intcontroller.h"

/* Port B interface implementation */

int portB_conf(int pin, enum port_mode mode) {
	int ret = 0;
	if (pin < 0 || pin > 10)
		return -1;

	if (mode == SIGOUT)
		rPCONB |= INT_BIT(pin);
	else if (mode == OUTPUT)
		rPCONB &= ~INT_BIT(pin);
	else
		ret = -1;

	return ret;
}

int portB_write(int pin, enum digital val) {
	if (pin < 0 || pin > 10)
		return -1;

	if (val < 0 || val > 1)
		return -1;

	if (val)
		rPDATB |= INT_BIT(pin);
	else
		rPDATB &= ~INT_BIT(pin);

	return 0;
}

/* Port G interface implementation */

int portG_conf(int pin, enum port_mode mode) {
	int pos = pin * 2;

	if (pin < 0 || pin > 7)
		return -1;

	switch (mode) {
	case INPUT:
		rPCONG &= ~(0x3 << pos);
		break;
	case OUTPUT:
		rPCONG &= ~(0x3 << pos);
		rPCONG |= (0x1 << pos);
		break;
	case SIGOUT:
		rPCONG &= ~(0x3 << pos);
		rPCONG |= (0x2 << pos);
		break;
	case EINT:
		rPCONG |= (0x3 << pos);
		break;
	default:
		return -1;
	}

	return 0;
}

int portG_eint_trig(int pin, enum trigger trig) {
	int pos = pin * 4;

	if (pin < 0 || pin > 7)
		return -1;

	switch (trig) {
	case LLOW:
		rEXTINT &= ~(0x7 << pos);
		break;
	case LHIGH:
		rEXTINT &= ~(0x7 << pos);
		rEXTINT |= (0x1 << pos);
		break;
	case FALLING:
		rEXTINT &= ~(0x7 << pos);
		rEXTINT |= (0x2 << pos);
		break;
	case RISING:
		rEXTINT &= ~(0x7 << pos);
		rEXTINT |= (0x4 << pos);
		break;
	case EDGE:
		rEXTINT &= ~(0x7 << pos);
		rEXTINT |= (0x6 << pos);
		break;
	default:
		return -1;
	}
	return 0;
}

int portG_write(int pin, enum digital val) {
	int pos = pin * 2;

	if (pin < 0 || pin > 7)
		return -1;

	if (val < 0 || val > 1)
		return -1;

	if ((rPCONG & (0x3 << pos)) != (0x1 << pos))
		return -1;

	if (val)
		rPDATG |= (0x1 << pin);
	else
		rPDATG &= ~(0x1 << pin);

	return 0;
}

int portG_read(int pin, enum digital* val) {
	int pos = pin * 2;

	if (pin < 0 || pin > 7)
		return -1;

	if (rPCONG & (0x3 << pos))
		return -1;

	if (rPDATG & (0x1 << pin))
		*val = HIGH;
	else
		*val = LOW;

	return 0;
}

int portG_conf_pup(int pin, enum enable st) {
if (pin < 0 || pin > 7)
	return -1;

if (st != ENABLE && st != DISABLE)
	return -1;

if (st == ENABLE)
	rPUPG &= ~INT_BIT(pin);
else
	rPUPG |= INT_BIT(pin);

return 0;
}


#include <chip.hpp>
#include <SysTick.hpp>

using namespace common;

namespace Device {
namespace Tick {

static uint64_t tick;
static constexpr uint64_t bit24 = (1u << 24);
static constexpr uint64_t mask = bit24 - 1;

//システムモニタ用タイマーの初期化
void Init() {
	auto *p = SysTick;
	SysTick_Config(mask);
	tick = 0;
}

uint64_t Tick() {
	auto *p = SysTick;
	return tick + (bit24 - (p->LOAD));
}

uint64_t TickUs() {
	return Tick() *100000/SystemCoreClock;
}

uint64_t TickMs() {
	return Tick() *1000/  SystemCoreClock;
}

uint64_t TickS(){
	return Tick()/SystemCoreClock;
}

void DelayUs(uint64_t us) {
	uint64_t time = TickUs() + us;
	while (TickUs() < time) {
		__NOP();
	}
}

void DelayMs(uint64_t ms) {
	uint64_t time = TickMs() + ms;
	while (TickMs() < time) {
		__NOP();
	}
}

extern "C" void SysTick_Handler() {
	//SysTick_Config(mask);
	tick += bit24;
}

}
}

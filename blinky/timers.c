uint32_t ui32SysClock;
ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000); // Run from the PLL at 120 MHz. SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0); // Enable the Timer 0 Module.

IntMasterEnable(); // Enable Master Interrupts
TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC); // Configure the 32-bit periodic timer.
TimerLoadSet(TIMER0_BASE, TIMER_A, ui32SysClock); // Load the timer value
TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler); // set the timer interrupt vector
TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // Enable the timer interrupt
TimerEnable(TIMER0_BASE, TIMER_A); // Enable the timers.

void Timer0IntHandler(void) {
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // Clear the timer interrupt. IntMasterDisable(); // Disable Interrupts
    GPIO_PORTQ_DATA_R ^= GPIO_PIN_7; //Toggle LED
    IntMasterEnable(); //Enable Interrupts

}

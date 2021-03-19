/*
 * pendant is wired as follows:
 * 
 * Emergency stop is connected across the outer pins and is normally closed. i
 * will need to change this to left and center pins as normally open.
 * 
 *  left     blu
 *  middle   n/c (will become blu/blk
 *  right    blu/blk
 * 
 * press switch wiring (pendant actvive when pressed)
 * 
 *  top    red (to pcb to enable switches)
 *  midle  ora/blk
 *  bottom n/c
 * 
 * PCB Wiring
 *  x1     gry
 *  x10    gry/blk
 *  x100   ora
 * 
 *  (red from switch)
 * 
 *  LED+   grn/blk
 *  LED-   wht/blk
 * 
 *  X      yel
 *  Y      yel/blk
 *  Z      brn
 *  4      brn/blk (4th axis - not used)
 * 
 * rotary encoder wiring
 * 
 *    A   B   0v  5v
 *    
 *        #A  #B  
 * 
 *  A      grn  
 *  B      wht
 *  0v     blk
 *  5v     red
 *  #A     vio     (not used)
 *  #B     vio/blk (not used)
 *  
 *  The following wires are not connected within the pendant
 *  
 *  red/blk
 *  pnk
 *  pnk/blk
 */

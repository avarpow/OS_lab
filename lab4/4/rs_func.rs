#![no_main]
use libc;
#[no_mangle]
pub extern "C" fn function_from_Rust(){
    libc::printf("This is a function from Rust.");
}
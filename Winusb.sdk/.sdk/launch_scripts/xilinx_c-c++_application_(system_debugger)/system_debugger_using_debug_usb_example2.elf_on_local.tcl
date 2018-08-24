connect -url tcp:127.0.0.1:3121
source D:/WorkingDirectory/Ottawa_workingDir/Misc/Winusb/Winusb.sdk/design_1_wrapper_hw_platform_2/ps7_init.tcl
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Zybo Z7 210351A6CA4FA"} -index 0
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent Zybo Z7 210351A6CA4FA" && level==0} -index 1
fpga -file D:/WorkingDirectory/Ottawa_workingDir/Misc/Winusb/Winusb.sdk/design_1_wrapper_hw_platform_2/design_1_wrapper.bit
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Zybo Z7 210351A6CA4FA"} -index 0
loadhw -hw D:/WorkingDirectory/Ottawa_workingDir/Misc/Winusb/Winusb.sdk/design_1_wrapper_hw_platform_2/system.hdf -mem-ranges [list {0x40000000 0xbfffffff}]
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Zybo Z7 210351A6CA4FA"} -index 0
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zybo Z7 210351A6CA4FA"} -index 0
dow D:/WorkingDirectory/Ottawa_workingDir/Misc/Winusb/Winusb.sdk/USB_example2/Debug/USB_example2.elf
configparams force-mem-access 0
bpadd -addr &main

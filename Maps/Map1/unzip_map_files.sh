#!/usr/bin/perl

$DATA_FILE="Map1.gmbaap.gtm";
$GBA_MAP_DATA_UNZIPED=GBA_map_data_unziped;

if(!(-e $GBA_MAP_DATA_UNZIPED))
{
   mkdir $GBA_MAP_DATA_UNZIPED;
}

#@list = ("tar", "-C", "GBA_map_data_unziped", "-zxvf", "$DATA_FILE");
`tar -C GBA_map_data_unziped -zxvf $DATA_FILE`;
#syscall(@list);

#!/usr/bin/perl

$DATA_FILE=Map1.gmbaap.gtm

$GBA_MAP_DATA_UNZIPED=GBA_map_data_unziped;

main();

sub main()
{
   if(!(-e $GBA_MAP_DATA_UNZIPED))
   {
      mkdir $GBA_MAP_DATA_UNZIPED;
      print "Created $GBA_MAP_DATA_UNZIPED ....\n";
   }
   # if the file exists, back it up
   if(-e $DATA_FILE)
   {
      mv $DATA_FILE $DATA_FILE.bak;
   }

   # Now repackage that stuff B!
   tar -zcvf $GBA_MAP_DATA_UNZIPED $DATA_FILE;

}


sub find_file($$)
{
   my ($directory, $file_search) = @_;
   opendir(CUR_DIR, $directory) or
      die "Cannot open up $directory directory!";

   while(my $file = readdir(CUR_DIR))
   {
      print "$file\n";
      if($file =~m/^$file_search$/)
      {
         close(CUR_DIR);
         return true;
      }
   }
   close(CUR_DIR);
   return false;
}
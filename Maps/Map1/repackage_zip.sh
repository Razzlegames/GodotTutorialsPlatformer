#!/usr/bin/perl

$DATA_FILE="Map1\.gmbaap\.gtm";

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
      # Make sure we don't overwrite a previous backup
      my $DATA_FILE_BAK = $DATA_FILE;
      my $i = 0;
      while(-e $DATA_FILE_BAK."".$i."\.bak")
      {
         $i++;
      }
      `mv $DATA_FILE "$DATA_FILE_BAK$i.bak"`;
   }

   # Now repackage that stuff B!
   `cd $GBA_MAP_DATA_UNZIPED/; tar -zvcf $DATA_FILE ./*; mv $DATA_FILE ../`;
   #`cp -f $GBA_MAP_DATA_UNZIPED/*gtm ./`;

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
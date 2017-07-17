# compile shaders offline
use strict;
use warnings;

my $shader_dir = '..\res\shaders';
my $header_dir = '..\compiled_shaders';
my $final_name = $header_dir.'\\'.'sheders.h';
my $prefix = "// this file is generated by compile_shader.pl, do not modify it directly.\n";

# compile the shader
# parameter: str - the filename
# no return
sub compile
{
    my $filename = $_[0];
    my @strs = split /\./, $filename;
    my $include = '#include';
    # shader name with dir
    my $in_fname = $shader_dir.'\\'.$filename;
    
    # raw shader type
    my $rst = $strs[1];
    # print "rst: $rst\n";
    
    # shader type: use shader model 5.0
    my $st = $rst."_5_0";
    # print "st: $st\n";
    
    # entry point
    my $ep = $strs[0]."_".$rst;
    # print "ep: $ep\n";
    
    # header name
    my $hn = $ep.".h";
    my $hn_n_dir = $header_dir.'\\'.$ep.'.h';
    # print "hn: $hn\n";

    print "compiling $in_fname\n";
    my @args = ("C:\\Program Files (x86)\\Windows Kits\\10\\bin\\x64\\fxc.exe"
		, "/Od", "/Zi", "/E", $ep, "/T", $st, "/Fh", $hn_n_dir, $in_fname);
    system(@args) == 0
	or die "system @args failed: $?";

    print FILE "$include \"$hn\"\n";
}

# use regex to match the filename and compile shaders
sub check_n_compile
{
    # get the parameter
    my $in_str = $_[0];
    
    if($in_str =~ /\.vs\.hlsl/
	or $in_str =~ /\.ps\.hlsl/) {
	compile($in_str);
    }
}

opendir(DIR ,$shader_dir) or die $!;

# always make a new dir
mkdir $header_dir;
# open the header and add compiled filename
open(FILE, '>'.$final_name) or die $!;

print FILE "$prefix\n";

while (my $file = readdir(DIR))
{
    check_n_compile($file);
}
close FILE;
closedir DIR;

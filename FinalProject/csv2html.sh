#add <TR><TD> at beginning of line; </TD>/TR> at end of line; replace ',' with <TR><TD>
sed -e 's|,|</TD><TD>|g' -e 's|^|<TR><TD>|' -e 's|$|</TD></TR>|' $1 > $2

#add first line <TABLE>
sed -i '1 i<TABLE>' $2

#add last line </TABLE>
sed -i -e '$a</TABLE>' $2

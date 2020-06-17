var a, b, c, i : int;
var d : () : int;
function get_counter() : () : int 
	var a : int;
	function inc() : int
		begin
			a := a + 1;
			inc := a;
		end
	begin
		a := 0;
		get_counter := inc;
	end
begin
	i := 0;
	a := 0;
	b := get_counter()();
	
	for i := 1 to 20 do
	begin
		c := a + b;
		a := b;
		b := c;
		
		writeln(a);
	end
	
	d := get_counter();
	writeln(d());
	writeln(d());
	writeln(d());
	
end.
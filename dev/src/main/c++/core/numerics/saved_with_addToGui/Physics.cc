#include <Physics.h>


Physics :: Physics() :
	name_("TestPhys"),
	dim("Dimension", 3),
	precision("Precision", 0.0001),
	oneFF(new OneFluxFunction("MyOneFluxFunction")),
	oneC("MyOneCurve", oneFF),
	macros("MACROS")
{
	addToUI(dim, true, false);
	addToUI(precision, false, false);
	addToUI(*oneFF);
	addToUI(oneC);

	macros.createMacro("Macro Name 1");
	macros.addToMacro(9,5);
	macros.addToMacro(9,5);
	addToUI(macros);
}


string Physics :: name(void)
{
	return name_;
}


void Physics :: show(void)
{
	cout << "Show in Physics\n";
	string xml;
	xml = dim.toXML();
	cout << xml;
}



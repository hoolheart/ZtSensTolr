# ZtSensTolr

A program to perform the sensitivity and tolerance analysis.

### Data Structure v0.0.1
> Date: June 27th, 2013

	Project:complex
	    Info:complex
	        Name:string
	        Team:string
	        Createdtime:timestamp
	        Modifiedtime:complex
	            Component:timestamp
	            Feature:timestamp
	            Orth:timestamp
	            Sens:timestamp
	    Components:list_complex(Component)
	        Id:string
	        Name:string
	        Value:double
	        Unit:string
	        Description:string
	    Features:list_feature(Feature)
	        Id:string
	        Name:string
	        Unit:string
	        Description:string
	    Orthplan:complex
	        Components:table
	        Features:table
	        Status:list_boolean
	    Senstable:table

### Actions v0.0.1
> Date: July 28th,2013

_For components:_

	bool addComponent(_id:string,_name:string,_value:double,_unit="":string,_des="":string);
	bool modifyComponent(id:string,attr:string,value:string);
	bool deleteComponent(id:string);
        void updateComponents();
	bool generateOrthogonalTable();

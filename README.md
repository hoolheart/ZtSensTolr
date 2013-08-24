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

_For components:_
> Date: July 28th, 2013

    bool addComponent(_id:string,_name:string,_value:double,_unit="":string,_des="":string);
    bool modifyComponent(id:string,attr:string,value:string);
    bool deleteComponent(id:string);
    void updateComponents();

_For features:_
> Date: August 15th, 2013

    bool addFeature(_id:string,_name:string,_unit="":string,_des="":string);
    bool modifyFeature(id:string,attr:string,value:string);
    bool deleteFeature(id:string);
    void updateFeatures();

_For orthogonal table:_
> Date: August 15th, 2013

    bool generateOrthogonalTable();
    bool fillOrthogonalExpriment(i:int,values:string_list);
    bool clearOrthogonalExpriment(i:int);
    void updateOrthogonalTable();

### Table View
> Date: August 24th, 2013

Based on the data-oriented structure, the class *TableView* only concerns the related data and shows it properly.

<h1>ZtSensTolr</h1>
===========================================================

A program to perform the sensitivity and tolrance analysis.

<h3>Data struct v0.1</h3>
---- June 27th, 2013

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

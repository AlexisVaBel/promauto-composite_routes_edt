#pragma once

// suffix means screen to wich sql/dml belongs to



static const char * SELECT_SUBROUTES_RTS      = " select id, name, descr, code, rootbegin, rootend subroot from roots where subroot = 1";
static const char * SELECT_ROUTE_SUBS_RTS     = " select sr.id, sr.root_id, sr.subroot_id, r.name, r.rootbegin, r.rootend from subroots sr, roots r where (r.id=sr.subroot_id) and (sr.root_id=%id%)";

static const char * SELECT_ROUTE_DEVS_RTS     = "select d.id, d.name, rd.timestart, rd.timestop, rd.ordernum, rd.fl_armo, rd.fl_transparent, rd.fl_ctrlprod, rd.fl_prod, rd.dly_prodstop, rd.fl_ctrlonly, rd.fl_soleowner, rd.device_id from rootdevices rd, devices d where (rd.root_id = %1)  and (rd.device_id=d.id) order by ordernum";
                                                                                                                                                                                                                  //select d.name  from rootdevices rd, devices d where (rd.root_id = %1) and (rd.device_id = d.id)
static const char * SELECT_ALL_DEVS_MCHB      = "select id, name from devices where devtype = 'MCHB'  order by name";

// dml
static const char * INSERT_SUB_TO_ROUTE                = "INSERT INTO SUBROOTS(ROOT_ID, SUBROOT_ID)  VALUES(%1, %2)";

static const char * DELETE_SUB_FROM_ROUTE              = "DELETE FROM SUBROOTS where id = %1";
static const char * DELETE_SUB_DEVICES_FROM_ROUTE      = "DELETE FROM ROOTDEVICES where root_id = %1 and device_id = %2";

/*

*/

/* subroots devices
SELECT
    D.NAME,
    RD.TIMESTART,
    RD.TIMESTOP,
    RD.ORDERNUM,
    RD.FL_ARMO,
    RD.FL_TRANSPARENT,
    RD.FL_CTRLPROD,
    RD.FL_PROD,
    RD.DLY_PRODSTOP,
    RD.FL_CTRLONLY,
    RD.FL_SOLEOWNER,
    RD.DEVICE_ID 
FROM
    ROOTDEVICES RD,
    DEVICES D
WHERE
    (RD.ROOT_ID = :SUBROOT_ID) AND
    (RD.DEVICE_ID=D.ID)
ORDER BY ORDERNUM


//code for insert devices from group

  while not dsSubrootsM.eof do begin
    dsSubrootsD.First;
    while not dsSubrootsD.eof do begin

      // Ïîèñê
      if dsROOTDEVICES.Locate('DEVICE_ID', dsSubrootsDDEVICE_ID.AsInteger, []) then begin
        dsROOTDEVICES.Edit;
      end else begin
        dsROOTDEVICES.Append;
      end;
      dsROOTDEVICESDEVICE_ID.AsInteger := dsSubrootsDDEVICE_ID.AsInteger;
      dsROOTDEVICESTIMESTART.AsInteger := dsSubrootsDTIMESTART.AsInteger;
      dsROOTDEVICESTIMESTOP.AsInteger := dsSubrootsDTIMESTOP.AsInteger;
      dsROOTDEVICESFL_ARMO.AsInteger := dsSubrootsDFL_ARMO.AsInteger;
      dsROOTDEVICESFL_TRANSPARENT.AsInteger := dsSubrootsDFL_TRANSPARENT.AsInteger;
      dsROOTDEVICESFL_CTRLPROD.AsInteger := dsSubrootsDFL_CTRLPROD.AsInteger;
      dsROOTDEVICESFL_PROD.AsInteger := dsSubrootsDFL_PROD.AsInteger;
      dsROOTDEVICESFL_CTRLONLY.AsInteger := dsSubrootsDFL_CTRLONLY.AsInteger;
      dsROOTDEVICESFL_SOLEOWNER.AsInteger := dsSubrootsDFL_SOLEOWNER.AsInteger;
      dsROOTDEVICESDLY_PRODSTOP.AsInteger := dsSubrootsDDLY_PRODSTOP.AsInteger;
      dsROOTDEVICES.Post;

      dsROOTDEVICES.Edit;
      dsROOTDEVICESORDERNUM.AsInteger := i+1000; // kostyl, then it`ll be removed
      dsROOTDEVICES.Post;

      dsSubrootsD.Next;
      inc(i);
    end;
    dsSubrootsM.Next;
  end;


  dsROOTDEVICES.Database.Execute('DELETE FROM ROOTDEVICES WHERE (ORDERNUM<1000) and (ROOT_ID='+inttostr(root_id)+')');
  dsROOTDEVICES.Database.Execute('UPDATE ROOTDEVICES SET ORDERNUM=ORDERNUM-1000 WHERE ORDERNUM>=1000');


// edit subroutes -> nextlines

INSERT INTO ROOTS(
    ID,
    NAME,
    DESCR,
    SUBROOT
)
VALUES(
    :ID,
    :NAME,
    :DESCR,
    :SUBROOT
)


INSERT INTO ROOTS(
    ID,
    NAME,
    DESCR,
    SUBROOT,
    ROOTBEGIN,
    ROOTEND
)
VALUES(
    :ID,
    :NAME,
    :DESCR,
    1,
    :ROOTBEGIN,
    :ROOTEND
)


INSERT INTO ROOTDEVICES(
    ID,
    ROOT_ID,
    DEVICE_ID,
    TIMESTART,
    TIMESTOP,
    ORDERNUM, 
    FL_CTRLONLY,
    FL_ARMO,
    FL_TRANSPARENT,
    FL_CTRLPROD,
    FL_PROD,
    FL_SOLEOWNER,
    DLY_PRODSTOP
)
VALUES(
    :ID,
    :MAS_ID,
    :DEVICE_ID,
    :TIMESTART,
    :TIMESTOP,
    :ORDERNUM, 
    :FL_CTRLONLY,
    :FL_ARMO,
    :FL_TRANSPARENT,
    :FL_CTRLPROD,
    :FL_PROD,
    :FL_SOLEOWNER,
    :DLY_PRODSTOP
)




INSERT INTO ROOTDEVICES(
    ID,
    ROOT_ID,
    DEVICE_ID,
    TIMESTART,
    TIMESTOP,
    ORDERNUM,
    FL_CTRLONLY,
    FL_ARMO,
    FL_TRANSPARENT,
    FL_CTRLPROD,
    FL_PROD,
    FL_SOLEOWNER,
    DLY_PRODSTOP
)
VALUES(
    :ID,
    :MAS_ID,
    :DEVICE_ID,
    :TIMESTART,
    :TIMESTOP,
    :ORDERNUM,
    :FL_CTRLONLY,
    :FL_ARMO,
    :FL_TRANSPARENT,
    :FL_CTRLPROD,
    :FL_PROD,
    :FL_SOLEOWNER,
    :DLY_PRODSTOP
)


  if DataSet.FieldByName('FL_CTRLONLY').AsInteger>0 then s := s + 'Ê';

  if DataSet.FieldByName('FL_ARMO').AsInteger>0 then s := s + 'Í';

  if DataSet.FieldByName('FL_TRANSPARENT').AsInteger=1 then s := s + 'ÏðÇ ';
  if DataSet.FieldByName('FL_TRANSPARENT').AsInteger=2 then s := s + 'ÏðÐ ';
  if DataSet.FieldByName('FL_TRANSPARENT').AsInteger=3 then s := s + 'Ïð ';

  if DataSet.FieldByName('FL_CTRLPROD').AsInteger>0 then s := s + 'Êï';

  if DataSet.FieldByName('FL_PROD').AsInteger>0 then s := s + 'Ïä';

  if (DataSet.FieldByName('FL_PROD').AsInteger>0) and
        (DataSet.FieldByName('DLY_PRODSTOP').AsInteger>0)
  then
    s := s + DataSet.FieldByName('DLY_PRODSTOP').AsString;

  if DataSet.FieldByName('FL_SOLEOWNER').AsInteger>0 then s := s + 'È';

  DataSet.FieldByName('MODEFLAGS').AsString := s;


*/

// ~dml



static const char * SELECT_SUBROUTES_SUBS       = " select name, rootbegin, rootend, descr, code, id from roots where subroot = 1 ";
static const char * SELECT_SUBROUTE_DEVS_SUBS   = " select id, root_id, device_id from rootdevices where root_id = %id% ";


// all routes
static const char * SELECT_ROUTES_ALL         = " select id, name, descr, code, subroot from roots where subroot = 0";
static const char * SELECT_SUBS_IN_RT_ALL     = " select sr.id, sr.root_id, sr.subroot_id, r.name from subroots sr, roots r  where (r.id = sr.subroot_id) and (sr.root_id = %1 )";
static const char * SELECT_DEVS_IN_RT_ALL     = " select d.name as name, r.id, r.root_id, r.device_id, r.timestart, r.timestop, r.ordernum, r.FL_CTRLONLY, r.FL_ARMO, r.FL_TRANSPARENT, r.FL_CTRLPROD, r.FL_PROD, r.FL_SOLEOWNER, r.DLY_PRODSTOP from rootdevices r, devices d where root_id = %1 and d.id = r.device_id  order by ordernum";

static const char * INSERT_DEVS_TO_ROOTDEVICES1  = "INSERT INTO ROOTDEVICES( ROOT_ID, DEVICE_ID, TIMESTART, TIMESTOP, ORDERNUM, FL_CTRLONLY, FL_ARMO, FL_TRANSPARENT, FL_CTRLPROD, FL_PROD, FL_SOLEOWNER, DLY_PRODSTOP )";
static const char * INSERT_DEVS_TO_ROOTDEVICES2  = " VALUES(%1, %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12 ) ";



static const char * UPDATE_DEVS_IN_RT_ALL     = " update ROOTDEVICES set timestart = %1, timestop = %2 , ordernum = %3, FL_CTRLONLY = %4 , FL_ARMO =%5, FL_TRANSPARENT = %6, FL_CTRLPROD = %7, FL_PROD = %8, FL_SOLEOWNER = %9, DLY_PRODSTOP=%10 where id=%11";

//// subs from route dml
static const char * INSERT_ROUTE_ALL          = "INSERT INTO ROOTS(NAME) VALUES(\'%1\')";
static const char * UPDATE_ROUTE_ALL          = "UPDATE ROOTS set NAME = (\'%1\') where ID = %2";
static const char * DELETE_ROUTE_ALL          = "DELETE from ROOTS where ID = %1";
//// subs from route dml
static const char * DELETE_SUBROUTE_ALL       = "delete from subroots where ( root_id = %id% )";
//// devs from route dml
static const char * DELETE_DEVS_ALL           = "delete from rootdevices where ( id = %id% )";

//~all routes

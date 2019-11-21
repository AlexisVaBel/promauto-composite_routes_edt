#pragma once


#include <iostream>
#include <QString>

// some other struct for most cases
// getting more space but using compact code

struct StructRoots{
    uint id{0};
    uint code{0};
    uint subroot{0};
    QString name{""};
    QString descr{""};
    uint rootbegin{0};
    uint rootend{0};

    uint     root_id;
    uint     device_id;
    uint     subroot_id;

    // editable
    uint fl_transparent;     // FL_TRANSPARENT - Пр : 0 - , 1 - ПрЗ, 2 - ПрР , 3 - Пр
        // bitwise
    uint fl_ctronly;
    uint fl_armo;
    uint fl_ctrlprod;
    uint fl_prod;
    uint fl_soleowner;
        //~ bitwise
    uint dly_prodstop;
    uint order;

    uint time_start;
    uint time_stop;    
    // editable


    friend std::ostream& operator<< (std::ostream &ostr, const StructRoots & rts){
        ostr << "id: " << rts.id << " ; code: " << rts.code << "; subroot: " << rts.subroot << "; name: " << rts.name.toStdString() << "; descr: " << rts.descr.toStdString() << std::endl;
        return  ostr;
    }

    bool equal(StructRoots & that){
        return (this->id == that.id) &&
                (this->fl_transparent == that.fl_transparent ) &&
                (this->fl_armo == that.fl_armo) &&
                (this->fl_prod == that.fl_prod) &&
                (this->fl_ctronly == that.fl_ctronly) &&
                (this->fl_ctrlprod == that.fl_ctrlprod) &&
                (this->fl_soleowner == that.fl_soleowner) &&
                (this->dly_prodstop == that.dly_prodstop) &&
                (this->time_start == that.time_start) &&
                (this->time_stop == that.time_stop) &&
                (this->order == that.order);
    }

    bool equal(StructRoots * that){
        return (this->id == that->id) &&
                (this->fl_transparent == that->fl_transparent ) &&
                (this->fl_armo == that->fl_armo) &&
                (this->fl_prod == that->fl_prod) &&
                (this->fl_ctronly == that->fl_ctronly) &&
                (this->fl_ctrlprod == that->fl_ctrlprod) &&
                (this->fl_soleowner == that->fl_soleowner) &&
                (this->dly_prodstop == that->dly_prodstop) &&
                (this->time_start == that->time_start) &&
                (this->time_stop == that->time_stop) &&
                (this->order == that->order);
    }
};





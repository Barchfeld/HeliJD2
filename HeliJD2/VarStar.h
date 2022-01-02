//
// Created by astro on 26.12.2021.
//

#ifndef HJD_VARSTAR_H
#define HJD_VARSTAR_H


#include <string>
#include <vector>

class VarStar {
private:
    std::string searchName; // internal query

    // CDS
    std::string oType; // otype (variable type) from CDS
    std::string oName; // oname from CDS
    std::string coordStr; // jpos (ra & de as string) from CDS
    long double rectDeg; // jradeg from CDS
    long double declDeg; // jdedeg from CDS
    std::vector<std::string> alias; // alias from CDS

    // AAVSO
    std::string vsxType; // variable type
    std::string vsxName;
    long double vsxPeriod;
    long double vsxEpoch;
    std::string vsxMax;
    std::string vsxMin;
    std::string constellation;

    // GCVS
    long gcvsNNO; // starnumber and constellation number
    std::string gcvsName;
    std::string gcvsType; // variable Type
    long double gcvsPeriod;
    long double gcvsEpoch;
    std::string gcvsMax;
    std::string gcvsMin;


public:
    VarStar();

    VarStar(const std::string &searchName);




    const std::string &getSearchName() const;

    void setSearchName(const std::string &searchName);

    const std::string &getOType() const;

    void setOType(const std::string &oType);

    const std::string &getOName() const;

    void setOName(const std::string &oName);

    const std::string &getCoordStr() const;

    void setCoordStr(const std::string &coordStr);

    long double getRectDeg() const;

    void setRectDeg(long double rectDeg);

    long double getDeclDeg() const;

    void setDeclDeg(long double declDeg);

    const std::vector<std::string> &getAlias() const;

    void setAlias(const std::vector<std::string> &alias);

    const std::string &getVsxType() const;

    void setVsxType(const std::string &vsxType);

    const std::string &getVsxName() const;

    void setVsxName(const std::string &vsxName);

    long double getVsxPeriod() const;

    void setVsxPeriod(long double vsxPeriod);

    long double getVsxEpoch() const;

    void setVsxEpoch(long double vsxEpoch);

    const std::string &getVsxMax() const;

    void setVsxMax(const std::string &vsxMax);

    const std::string &getVsxMin() const;

    void setVsxMin(const std::string &vsxMin);

    const std::string &getConstellation() const;

    void setConstellation(const std::string &constellation);

    long getGcvsNno() const;

    void setGcvsNno(long gcvsNno);

    const std::string &getGcvsName() const;

    void setGcvsName(const std::string &gcvsName);

    const std::string &getGcvsType() const;

    void setGcvsType(const std::string &gcvsType);

    long double getGcvsPeriod() const;

    void setGcvsPeriod(long double gcvsPeriod);

    long double getGcvsEpoch() const;

    void setGcvsEpoch(long double gcvsEpoch);

    const std::string &getGcvsMax() const;

    void setGcvsMax(const std::string &gcvsMax);

    const std::string &getGcvsMin() const;

    void setGcvsMin(const std::string &gcvsMin);

    virtual ~VarStar();

};


#endif //HJD_VARSTAR_H

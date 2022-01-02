//
// Created by astro on 26.12.2021.
//

#include "VarStar.h"

VarStar::VarStar(const std::string &searchName) : searchName(searchName) {}

VarStar::~VarStar() {

}

const std::string &VarStar::getSearchName() const {
    return searchName;
}

void VarStar::setSearchName(const std::string &searchName) {
    VarStar::searchName = searchName;
}

const std::string &VarStar::getOType() const {
    return oType;
}

void VarStar::setOType(const std::string &oType) {
    VarStar::oType = oType;
}

const std::string &VarStar::getOName() const {
    return oName;
}

void VarStar::setOName(const std::string &oName) {
    VarStar::oName = oName;
}

const std::string &VarStar::getCoordStr() const {
    return coordStr;
}

void VarStar::setCoordStr(const std::string &coordStr) {
    VarStar::coordStr = coordStr;
}

long double VarStar::getRectDeg() const {
    return rectDeg;
}

void VarStar::setRectDeg(long double rectDeg) {
    VarStar::rectDeg = rectDeg;
}

long double VarStar::getDeclDeg() const {
    return declDeg;
}

void VarStar::setDeclDeg(long double declDeg) {
    VarStar::declDeg = declDeg;
}

const std::vector<std::string> &VarStar::getAlias() const {
    return alias;
}

void VarStar::setAlias(const std::vector<std::string> &alias) {
    VarStar::alias = alias;
}

const std::string &VarStar::getVsxType() const {
    return vsxType;
}

void VarStar::setVsxType(const std::string &vsxType) {
    VarStar::vsxType = vsxType;
}

const std::string &VarStar::getVsxName() const {
    return vsxName;
}

void VarStar::setVsxName(const std::string &vsxName) {
    VarStar::vsxName = vsxName;
}

long double VarStar::getVsxPeriod() const {
    return vsxPeriod;
}

void VarStar::setVsxPeriod(long double vsxPeriod) {
    VarStar::vsxPeriod = vsxPeriod;
}

long double VarStar::getVsxEpoch() const {
    return vsxEpoch;
}

void VarStar::setVsxEpoch(long double vsxEpoch) {
    VarStar::vsxEpoch = vsxEpoch;
}

const std::string &VarStar::getVsxMax() const {
    return vsxMax;
}

void VarStar::setVsxMax(const std::string &vsxMax) {
    VarStar::vsxMax = vsxMax;
}

const std::string &VarStar::getVsxMin() const {
    return vsxMin;
}

void VarStar::setVsxMin(const std::string &vsxMin) {
    VarStar::vsxMin = vsxMin;
}

const std::string &VarStar::getConstellation() const {
    return constellation;
}

void VarStar::setConstellation(const std::string &constellation) {
    VarStar::constellation = constellation;
}

long VarStar::getGcvsNno() const {
    return gcvsNNO;
}

void VarStar::setGcvsNno(long gcvsNno) {
    gcvsNNO = gcvsNno;
}

const std::string &VarStar::getGcvsName() const {
    return gcvsName;
}

void VarStar::setGcvsName(const std::string &gcvsName) {
    VarStar::gcvsName = gcvsName;
}

const std::string &VarStar::getGcvsType() const {
    return gcvsType;
}

void VarStar::setGcvsType(const std::string &gcvsType) {
    VarStar::gcvsType = gcvsType;
}

long double VarStar::getGcvsPeriod() const {
    return gcvsPeriod;
}

void VarStar::setGcvsPeriod(long double gcvsPeriod) {
    VarStar::gcvsPeriod = gcvsPeriod;
}

long double VarStar::getGcvsEpoch() const {
    return gcvsEpoch;
}

void VarStar::setGcvsEpoch(long double gcvsEpoch) {
    VarStar::gcvsEpoch = gcvsEpoch;
}

const std::string &VarStar::getGcvsMax() const {
    return gcvsMax;
}

void VarStar::setGcvsMax(const std::string &gcvsMax) {
    VarStar::gcvsMax = gcvsMax;
}

const std::string &VarStar::getGcvsMin() const {
    return gcvsMin;
}

void VarStar::setGcvsMin(const std::string &gcvsMin) {
    VarStar::gcvsMin = gcvsMin;
}

VarStar::VarStar() {

}

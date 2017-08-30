/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
class SEFluidCircuit;
class SEFluidCircuitNode;
class SEFluidCircuitPath;
class SEThermalCircuit;
class SEThermalCircuitNode;
class SEThermalCircuitPath;
class SEElectricalCircuit;
class SEElectricalCircuitNode;
class SEElectricalCircuitPath;
CDM_BIND_DECL(CircuitManagerData)


#define CIRCUIT_LEDGER_TEMPLATE typename NodeType, typename PathType, typename CircuitType
#define CIRCUIT_LEDGER_TYPES NodeType,PathType,CircuitType

template<CIRCUIT_LEDGER_TEMPLATE>
class SECircuitLedger
{
  friend class SECircuitManager;
protected:
  SECircuitLedger() {};
public:
  virtual ~SECircuitLedger() { Clear(); };
  void Clear();
  std::map<std::string, NodeType*>    nodes;
  std::map<std::string, PathType*>    paths;
  std::map<std::string, CircuitType*> circuits;
};

#define ELECTRICAL_LEDGER_TYPES SEElectricalCircuitNode,SEElectricalCircuitPath,SEElectricalCircuit
#define FLUID_LEDGER_TYPES SEFluidCircuitNode,SEFluidCircuitPath,SEFluidCircuit
#define THERMAL_LEDGER_TYPES SEThermalCircuitNode,SEThermalCircuitPath,SEThermalCircuit

class CDM_DECL SECircuitManager : public Loggable
{
public:
  SECircuitManager(Logger* logger);
  virtual ~SECircuitManager();

  virtual void Clear(); //clear memory

  virtual void StateChange() { };
  bool LoadFile(const std::string& filename);
  void SaveFile(const std::string& filename);

  static void Load(const cdm::CircuitManagerData& src, SECircuitManager& dst);
  static cdm::CircuitManagerData* Unload(const SECircuitManager& src);
protected:
  static void Serialize(const cdm::CircuitManagerData& src, SECircuitManager& dst);
  static void Serialize(const SECircuitManager& src, cdm::CircuitManagerData& dst);

public:
  void SetReadOnly(bool b);  
protected:
  

public:
  virtual SEElectricalCircuitNode&       CreateElectricalNode(const std::string& name)                                                             { return CreateNode<ELECTRICAL_LEDGER_TYPES>(name, m_ElectricalLedger); }
  virtual void                           DeleteElectricalNode(const std::string& name)                                                             {        DeleteNode<ELECTRICAL_LEDGER_TYPES>(name, m_ElectricalLedger); }
  virtual bool                           HasElectricalNode(const std::string& name) const                                                          { return HasNode<ELECTRICAL_LEDGER_TYPES>(name, m_ElectricalLedger); }
  virtual SEElectricalCircuitNode*       GetElectricalNode(const std::string& name)                                                                { return GetNode<ELECTRICAL_LEDGER_TYPES>(name, m_ElectricalLedger); }
  virtual const SEElectricalCircuitNode* GetElectricalNode(const std::string& name) const                                                          { return GetNode<ELECTRICAL_LEDGER_TYPES>(name, m_ElectricalLedger); }
  virtual SEElectricalCircuitPath&       CreateElectricalPath(SEElectricalCircuitNode& src, SEElectricalCircuitNode& tgt, const std::string& name) { return CreatePath<ELECTRICAL_LEDGER_TYPES>(src,tgt,name, m_ElectricalLedger); }
  virtual void                           DeleteElectricalPath(const std::string& name)                                                             {        DeletePath<ELECTRICAL_LEDGER_TYPES>(name, m_ElectricalLedger); }
  virtual bool                           HasElectricalPath(const std::string& name) const                                                          { return HasPath<ELECTRICAL_LEDGER_TYPES>(name, m_ElectricalLedger); }
  virtual SEElectricalCircuitPath*       GetElectricalPath(const std::string& name)                                                                { return GetPath<ELECTRICAL_LEDGER_TYPES>(name, m_ElectricalLedger); }
  virtual const SEElectricalCircuitPath* GetElectricalPath(const std::string& name) const                                                          { return GetPath<ELECTRICAL_LEDGER_TYPES>(name, m_ElectricalLedger); }
  virtual SEElectricalCircuit&           CreateElectricalCircuit(const std::string& name)                                                          { return CreateCircuit<ELECTRICAL_LEDGER_TYPES>(name, m_ElectricalLedger); }
  virtual void                           DeleteElectricalCircuit(const std::string& name)                                                          {        DeleteCircuit<ELECTRICAL_LEDGER_TYPES>(name, m_ElectricalLedger); }
  virtual bool                           HasElectricalCircuit(const std::string& name) const                                                       { return HasCircuit<ELECTRICAL_LEDGER_TYPES>(name, m_ElectricalLedger); }
  virtual SEElectricalCircuit*           GetElectricalCircuit(const std::string& name)                                                             { return GetCircuit<ELECTRICAL_LEDGER_TYPES>(name, m_ElectricalLedger); }
  virtual const SEElectricalCircuit*     GetElectricalCircuit(const std::string& name) const                                                       { return GetCircuit<ELECTRICAL_LEDGER_TYPES>(name, m_ElectricalLedger); }
  virtual void                           SetReadOnlyElectrical(bool b);
protected:                        
  SECircuitLedger<SEElectricalCircuitNode,SEElectricalCircuitPath,SEElectricalCircuit> m_ElectricalLedger;

public:
  virtual SEFluidCircuitNode&            CreateFluidNode(const std::string& name)                                                                  { return CreateNode<FLUID_LEDGER_TYPES>(name, m_FluidLedger); }
  virtual void                           DeleteFluidNode(const std::string& name)                                                                  {        DeleteNode<FLUID_LEDGER_TYPES>(name, m_FluidLedger); }
  virtual bool                           HasFluidNode(const std::string& name) const                                                               { return HasNode<FLUID_LEDGER_TYPES>(name, m_FluidLedger); }
  virtual SEFluidCircuitNode*            GetFluidNode(const std::string& name)                                                                     { return GetNode<FLUID_LEDGER_TYPES>(name, m_FluidLedger); }
  virtual const SEFluidCircuitNode*      GetFluidNode(const std::string& name) const                                                               { return GetNode<FLUID_LEDGER_TYPES>(name, m_FluidLedger); }
  virtual SEFluidCircuitPath&            CreateFluidPath(SEFluidCircuitNode& src, SEFluidCircuitNode& tgt, const std::string& name)                { return CreatePath<FLUID_LEDGER_TYPES>(src,tgt,name, m_FluidLedger); }
  virtual void                           DeleteFluidPath(const std::string& name)                                                                  {        DeletePath<FLUID_LEDGER_TYPES>(name, m_FluidLedger); }
  virtual bool                           HasFluidPath(const std::string& name) const                                                               { return HasPath<FLUID_LEDGER_TYPES>(name, m_FluidLedger); }
  virtual SEFluidCircuitPath*            GetFluidPath(const std::string& name)                                                                     { return GetPath<FLUID_LEDGER_TYPES>(name, m_FluidLedger); }
  virtual const SEFluidCircuitPath*      GetFluidPath(const std::string& name) const                                                               { return GetPath<FLUID_LEDGER_TYPES>(name, m_FluidLedger); }
  virtual SEFluidCircuit&                CreateFluidCircuit(const std::string& name)                                                               { return CreateCircuit<FLUID_LEDGER_TYPES>(name, m_FluidLedger); }
  virtual void                           DeleteFluidCircuit(const std::string& name)                                                               {        DeleteCircuit<FLUID_LEDGER_TYPES>(name, m_FluidLedger); }
  virtual bool                           HasFluidCircuit(const std::string& name) const                                                            { return HasCircuit<FLUID_LEDGER_TYPES>(name, m_FluidLedger); }
  virtual SEFluidCircuit*                GetFluidCircuit(const std::string& name)                                                                  { return GetCircuit<FLUID_LEDGER_TYPES>(name, m_FluidLedger); }
  virtual const SEFluidCircuit*          GetFluidCircuit(const std::string& name) const                                                            { return GetCircuit<FLUID_LEDGER_TYPES>(name, m_FluidLedger); }
  virtual void                           SetReadOnlyFluid(bool b);
protected:
  SECircuitLedger<SEFluidCircuitNode, SEFluidCircuitPath, SEFluidCircuit> m_FluidLedger;

public:
   virtual SEThermalCircuitNode&         CreateThermalNode(const std::string& name)                                                                { return CreateNode<THERMAL_LEDGER_TYPES>(name, m_ThermalLedger); }
  virtual void                           DeleteThermalNode(const std::string& name)                                                                {        DeleteNode<THERMAL_LEDGER_TYPES>(name, m_ThermalLedger); }
  virtual bool                           HasThermalNode(const std::string& name) const                                                             { return HasNode<THERMAL_LEDGER_TYPES>(name, m_ThermalLedger); }
  virtual SEThermalCircuitNode*          GetThermalNode(const std::string& name)                                                                   { return GetNode<THERMAL_LEDGER_TYPES>(name, m_ThermalLedger); }
  virtual const SEThermalCircuitNode*    GetThermalNode(const std::string& name) const                                                             { return GetNode<THERMAL_LEDGER_TYPES>(name, m_ThermalLedger); }
  virtual SEThermalCircuitPath&          CreateThermalPath(SEThermalCircuitNode& src, SEThermalCircuitNode& tgt, const std::string& name)          { return CreatePath<THERMAL_LEDGER_TYPES>(src,tgt,name, m_ThermalLedger); }
  virtual void                           DeleteThermalPath(const std::string& name)                                                                {        DeletePath<THERMAL_LEDGER_TYPES>(name, m_ThermalLedger); }
  virtual bool                           HasThermalPath(const std::string& name) const                                                             { return HasPath<THERMAL_LEDGER_TYPES>(name, m_ThermalLedger); }
  virtual SEThermalCircuitPath*          GetThermalPath(const std::string& name)                                                                   { return GetPath<THERMAL_LEDGER_TYPES>(name, m_ThermalLedger); }
  virtual const SEThermalCircuitPath*    GetThermalPath(const std::string& name) const                                                             { return GetPath<THERMAL_LEDGER_TYPES>(name, m_ThermalLedger); }
  virtual SEThermalCircuit&              CreateThermalCircuit(const std::string& name)                                                             { return CreateCircuit<THERMAL_LEDGER_TYPES>(name, m_ThermalLedger); }
  virtual void                           DeleteThermalCircuit(const std::string& name)                                                             {        DeleteCircuit<THERMAL_LEDGER_TYPES>(name, m_ThermalLedger); }
  virtual bool                           HasThermalCircuit(const std::string& name) const                                                          { return HasCircuit<THERMAL_LEDGER_TYPES>(name, m_ThermalLedger); }
  virtual SEThermalCircuit*              GetThermalCircuit(const std::string& name)                                                                { return GetCircuit<THERMAL_LEDGER_TYPES>(name, m_ThermalLedger); }
  virtual const SEThermalCircuit*        GetThermalCircuit(const std::string& name) const                                                          { return GetCircuit<THERMAL_LEDGER_TYPES>(name, m_ThermalLedger); }
  virtual void                           SetReadOnlyThermal(bool b);
protected:
  SECircuitLedger<SEThermalCircuitNode, SEThermalCircuitPath, SEThermalCircuit> m_ThermalLedger;


protected:
  template<CIRCUIT_LEDGER_TEMPLATE> NodeType&          CreateNode(const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger);
  template<CIRCUIT_LEDGER_TEMPLATE> void               DeleteNode(const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger);
  template<CIRCUIT_LEDGER_TEMPLATE> bool               HasNode(const std::string& name, const SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger) const;
  template<CIRCUIT_LEDGER_TEMPLATE> NodeType*          GetNode(const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger);
  template<CIRCUIT_LEDGER_TEMPLATE> const NodeType*    GetNode(const std::string& name, const SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger) const;
  template<CIRCUIT_LEDGER_TEMPLATE> PathType&          CreatePath(NodeType& src, NodeType& tgt, const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger);
  template<CIRCUIT_LEDGER_TEMPLATE> void               DeletePath(const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger);
  template<CIRCUIT_LEDGER_TEMPLATE> bool               HasPath(const std::string& name, const SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger) const;
  template<CIRCUIT_LEDGER_TEMPLATE> PathType*          GetPath(const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger);
  template<CIRCUIT_LEDGER_TEMPLATE> const PathType*    GetPath(const std::string& name, const SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger) const;
  template<CIRCUIT_LEDGER_TEMPLATE> CircuitType&       CreateCircuit(const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger);
  template<CIRCUIT_LEDGER_TEMPLATE> void               DeleteCircuit(const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger);
  template<CIRCUIT_LEDGER_TEMPLATE> bool               HasCircuit(const std::string& name, const SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger) const;
  template<CIRCUIT_LEDGER_TEMPLATE> CircuitType*       GetCircuit(const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger);
  template<CIRCUIT_LEDGER_TEMPLATE> const CircuitType* GetCircuit(const std::string& name, const SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger) const;
};